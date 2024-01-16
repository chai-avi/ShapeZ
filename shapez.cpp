#include "shapez.h"
#include "ui_shapez.h"
ShapeZ::ShapeZ(QWidget *parent) :
    QWidget(parent)
{
//    map = new Map(GAME_WIDTH/30, GAME_HEIGHT/30, 2);
    initScene();
}

ShapeZ::~ShapeZ()
{
    delete ui;
}
void ShapeZ::initScene(){
    setFixedSize(GAME_WIDTH,GAME_HEIGHT);
    setWindowTitle(GAME_TITLE);
    //开始游戏
    gamescene = new scenes();
    start = new startscene();
    shop = new shopscene;
    start->show();
    //连接界面之间的信号和槽
    connect(&start->newgameButton, &mypushbutton::clicked, this, [=](){
        play = new playscene();
        play->show();
        start->close();
        connect(&play->exitButton, &mypushbutton::clicked, this, [=](){
            start->show();
            play->close();
            scenes::money = play->map->coin;
            qDebug()<<"money "<<scenes::money;
            delete play;
            qDebug()<<"money "<<scenes::money;
        });
    });
    connect(&start->storeButton, &mypushbutton::clicked, this, [=](){
        shop->coinlabel.setText(QString::number(scenes::money));
        shop->show();
        start->close();
    });
    connect(&shop->exitButton, &mypushbutton::clicked, this, [=](){
        start->show();
        shop->close();
    });
    //存档
    connect(&play->loadButton, &mypushbutton::clicked, this, &ShapeZ::saveload);
}
void ShapeZ::saveload(){
    QSettings settings("chai_avi", "myShapeZ");
    //全局变量
    settings.setValue("MineUp", scenes::mineUp);
    settings.setValue("MapUp", scenes::mapUp);
    settings.setValue("MoneyUp", play->map->coin);
    settings.setValue("Money", scenes::money);
    //局部参数
    settings.setValue("Level", play->map->level);
    QMap<int, int> map1;
    for (auto it = play->map->gridMap.begin(); it != play->map->gridMap.end(); ++it) {
        map1[it.key().x*100+it.key().y] = it.value();
    }
    QVariant mapVariant = QVariant::fromValue(map1);
    settings.setValue("GridMap", mapVariant);
    map1.clear();
    for (auto it = play->map->mineMap.begin(); it != play->map->mineMap.end(); ++it) {
        map1[it.key().x*100+it.key().y] = it.value();
    }
    mapVariant = QVariant::fromValue(map1);
    settings.setValue("MineMap", mapVariant);

    settings.setValue("FinishedTask", play->finishedTask);

    settings.setValue("TaskFlag1", play->taskFlag[1]);
    settings.setValue("TaskFlag2", play->taskFlag[2]);
    settings.setValue("TaskFlag3", play->taskFlag[3]);

    settings.setValue("UpFlag1", play->upFlag[1]);
    settings.setValue("UpFlag2", play->upFlag[2]);
    settings.setValue("UpFlag3", play->upFlag[3]);

    map1.clear();
    for (auto it = Installations::InstallMap.begin(); it != Installations::InstallMap.end(); ++it) {
        map1[it.key().x*100+it.key().y] = it.value()->dir;
    }
    mapVariant = QVariant::fromValue(map1);
    settings.setValue("InstallDir", mapVariant);
    map1.clear();
    for (auto it = Goods::goodsMap.begin(); it != Goods::goodsMap.end(); ++it) {
        map1[it.key().x*100+it.key().y] = it.value()->dir;
    }
    mapVariant = QVariant::fromValue(map1);
    settings.setValue("GoodDir", mapVariant);
    map1.clear();
    for (auto it = Goods::goodsMap.begin(); it != Goods::goodsMap.end(); ++it) {
        map1[it.key().x*100+it.key().y] = it.value()->type;
    }
    mapVariant = QVariant::fromValue(map1);
    settings.setValue("GoodType", mapVariant);
}
