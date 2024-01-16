#include "shapez.h"
#include "ui_shapez.h"
ShapeZ::ShapeZ(QWidget *parent) :
    QWidget(parent)
{
    initScene();
}

ShapeZ::~ShapeZ()
{
//    delete ui;
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
            delete play;
        });
        connect(&play->loadButton, &mypushbutton::clicked, this, &ShapeZ::saveload);
    });
    connect(&start->storeButton, &mypushbutton::clicked, this, [=](){
        shop->coinlabel.setText(QString::number(scenes::money));
        shop->show();
        start->close();
    });
    connect(&start->exitButton, &mypushbutton::clicked, this, [=](){
        start->close();
        this->close();
    });
    connect(&shop->exitButton, &mypushbutton::clicked, this, [=](){
        start->show();
        shop->close();
    });
    //存档
    connect(&start->loadButton, &mypushbutton::clicked, this, &ShapeZ::loadload);
}

void ShapeZ::loadload(){
    //导入存档
    QFile file("savedgame.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        int tmp;
        in >> tmp;
        scenes::mineUp = tmp;
        in >> tmp;
        scenes::mapUp = tmp;
        in >> tmp;
        scenes::moneyUp = tmp;
        in >> tmp;
        scenes::money = tmp;

        play = new playscene;
        connect(&play->exitButton, &mypushbutton::clicked, this, [=](){
            start->show();
            play->close();
            scenes::money = play->map->coin;
            delete play;
        });
        connect(&play->loadButton, &mypushbutton::clicked, this, &ShapeZ::saveload);

        in >> play->map->level;
        in >> play->finishedTask;
        for(int i =1;i<=3;i++) {
            in >> tmp;
            play->taskFlag[i] = tmp;
        }
        for(int i =1;i<=3;i++) {
            in >> tmp;
            play->upFlag[i] = tmp;
        }
        for(int i =1;i<=3;i++) in >> play->map->handedGoods[i];
        in >> play->drillerspeed;
        play->drillerTime->start(play->drillerspeed);
        in >> play->beltspeed;
        play->beltTime->start(play->beltspeed);
        in >> play->cutterspeed;
        play->cutterTime->start(play->cutterspeed);

        int a,b,c,d;
        in>>tmp;
        //地图
        for (auto it = play->map->gridMap.begin(); it != play->map->gridMap.end(); ++it)  it.value() = 0;
        for(int i=0;i<tmp;i++){
            in >> a >> b >> c;
            play->map->gridMap[{a,b}] = c;
        }
        //开采物地块
        in>>tmp;
        for (auto it = play->map->mineMap.begin(); it != play->map->mineMap.end(); ++it)  it.value() = 0;
        for(int i=0;i<tmp;i++){
            in >> a >> b >> c;
            play->map->mineMap[{a,b}] = c;
        }
        //设备
        in>>tmp;
        Installations::InstallMap.clear();
        for(int i=0;i<tmp;i++){
            in >> a >> b >> c >> d;
            switch (c) {
            case 1:
                new driller({a,b}, d);
                break;
            case 2:
                new belt({a,b}, d);
                break;
            case 3:
                new cuter({a,b}, d);
                break;
            case 4:
                new trash({a,b});
                break;
            case 5:
                new rotater({a,b}, d);
                break;
            }
        }
        //物品
        in>>tmp;
        Goods::goodsMap.clear();
        for(int i=0;i<tmp;i++){
            in >> a >> b >> c >> d;
            Goods::goodsMap[{a,b}] = new Goods({a,b}, c, d);
        }
        file.close();
        play->show();
        start->close();
    }
}
void ShapeZ::saveload(){
    //存储存档
    qDebug()<<"topennnnnnnn";
    QFile file("savedgame.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << scenes::mineUp << '\n';
        out << scenes::mapUp << '\n';
        out << scenes::moneyUp << '\n';
        out << play->map->coin << '\n';
        out << play->map->level << '\n';
        out << play->finishedTask << '\n';
        for(int i =1;i<=3;i++) out << play->taskFlag[i] << ' ';
        out << '\n';
        for(int i =1;i<=3;i++) out << play->upFlag[i] << ' ';
        out << '\n';
        for(int i =1;i<=3;i++) out << play->map->handedGoods[i] << ' ';
        out << '\n';
        out << play->drillerspeed << '\n';
        out << play->beltspeed << '\n';
        out << play->cutterspeed << '\n';
        out << '\n';
        //地图格点
        out << play->map->gridMap.size() << '\n';
        for (auto it = play->map->gridMap.begin(); it != play->map->gridMap.end(); ++it) {
            out<<it.key().x<<' '<<it.key().y<<' '<<it.value()<<'\n';
        }
        out << '\n';
        //开采物地图
        out << play->map->mineMap.size() << '\n';
        for (auto it = play->map->mineMap.begin(); it != play->map->mineMap.end(); ++it) {
            out<<it.key().x<<' '<<it.key().y<<' '<<it.value()<<'\n';
        }
        out << '\n';
        //设备地图
        out << Installations::InstallMap.size() << '\n';
        for (auto it = Installations::InstallMap.begin(); it != Installations::InstallMap.end(); ++it) {
            out<<it.key().x<<' '<<it.key().y<<' '<<it.value()->type<<' '<<it.value()->dir<<'\n';
        }
        out << '\n';
        //物品地图
        out << Goods::goodsMap.size() << '\n';
        for (auto it = Goods::goodsMap.begin(); it != Goods::goodsMap.end(); ++it) {
            out<<it.key().x<<' '<<it.key().y<<' '<<it.value()->type<<' '<<it.value()->dir<<'\n';
        }
        out << '\n';
        file.close();
    }
}
