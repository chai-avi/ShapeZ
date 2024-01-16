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
            qDebug()<<"money "<<scenes::money;
            delete play;
            qDebug()<<"money "<<scenes::money;
        });
        connect(&play->loadButton, &mypushbutton::clicked, this, &ShapeZ::saveload);
    });
    connect(&start->storeButton, &mypushbutton::clicked, this, [=](){
        shop->coinlabel.setText(QString::number(scenes::money));
        shop->show();
        start->close();
    });
    connect(&start->exitButton, &mypushbutton::clicked, this, [=](){
        qDebug()<<"eixt";
        start->close();
        this->close();
    });
    connect(&shop->exitButton, &mypushbutton::clicked, this, [=](){
        start->show();
        shop->close();
    });
    //存档
    connect(&start->loadButton, &mypushbutton::clicked, this, [=](){
        loadload();
        play->show();
        start->close();
    });
}
//void ShapeZ::loadload(){
//    QSettings settings("shapeZ.ini", QSettings::IniFormat);
//    scenes::mineUp = settings.value("MineUp").toBool();
//    scenes::mapUp = settings.value("MapUp").toBool();
//    scenes::moneyUp = settings.value("MoneyUp").toBool();
//    scenes::money = settings.value("Money").toInt();
//    play->map->level = settings.value("Level").toInt();
//    qDebug()<<scenes::money;
////    play->finishedTask = settings.value("FinishedTask").toInt();
//}
void ShapeZ::loadload(){
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
            qDebug()<<"money "<<scenes::money;
            delete play;
            qDebug()<<"money "<<scenes::money;
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
        play->map->gridMap.clear();
        for(int i=0;i<tmp;i++){
            in >> a >> b >> c;
            play->map->gridMap[{a,b}] = c;
        }

        in>>tmp;
        play->map->mineMap.clear();
        for(int i=0;i<tmp;i++){
            in >> a >> b >> c;
            play->map->mineMap[{a,b}] = c;
        }

        in>>tmp;
        Installations::InstallMap.clear();
        for(int i=0;i<tmp;i++){
            in >> a >> b >> c >> d;
            switch (c) {
            case 1:
                Installations::InstallMap[{a,b}] = new driller({a,b}, d);
                break;
            case 2:
                Installations::InstallMap[{a,b}] = new belt({a,b}, d);
                break;
            case 3:
                Installations::InstallMap[{a,b}] = new cuter({a,b}, d);
                break;
            case 4:
                Installations::InstallMap[{a,b}] = new trash({a,b});
                break;
            case 5:
                Installations::InstallMap[{a,b}] = new rotater({a,b}, d);
                break;
            }
        }

        in>>tmp;
        Goods::goodsMap.clear();
        for(int i=0;i<tmp;i++){
            in >> a >> b >> c >> d;
            Goods::goodsMap[{a,b}] = new Goods({a,b}, c, d);
        }

        file.close();
    }
}
void ShapeZ::saveload(){

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

        out << play->map->gridMap.size() << '\n';
        for (auto it = play->map->gridMap.begin(); it != play->map->gridMap.end(); ++it) {
            out<<it.key().x<<' '<<it.key().y<<' '<<it.value()<<'\n';
        }
        out << '\n';

        out << play->map->mineMap.size() << '\n';
        for (auto it = play->map->mineMap.begin(); it != play->map->mineMap.end(); ++it) {
            out<<it.key().x<<' '<<it.key().y<<' '<<it.value()<<'\n';
        }
        out << '\n';

        out << Installations::InstallMap.size() << '\n';
        for (auto it = Installations::InstallMap.begin(); it != Installations::InstallMap.end(); ++it) {
            out<<it.key().x<<' '<<it.key().y<<' '<<it.value()->type<<' '<<it.value()->dir<<'\n';
        }
        out << '\n';

        out << Goods::goodsMap.size() << '\n';
        for (auto it = Goods::goodsMap.begin(); it != Goods::goodsMap.end(); ++it) {
            out<<it.key().x<<' '<<it.key().y<<' '<<it.value()->type<<' '<<it.value()->dir<<'\n';
        }
        out << '\n';

        file.close();
        qDebug()<<"opened";
    }
    else{
        qDebug()<<"notopen";
    }

}
//void ShapeZ::saveload(){
//    QSettings settings("shapeZ.ini", QSettings::IniFormat);
//    //全局变量
//    settings.setValue("MineUp", scenes::mineUp);
//    settings.setValue("MapUp", scenes::mapUp);
//    settings.setValue("MoneyUp", play->map->coin);
//    settings.setValue("Money", scenes::money);
//    qDebug()<<scenes::money<<' '<<settings.value("Money").toInt();
//    //局部参数
//    settings.setValue("Level", play->map->level);
////    settings.setValue("FinishedTask", play->finishedTask);

////    settings.setValue("TaskFlag1", play->taskFlag[1]);
////    settings.setValue("TaskFlag2", play->taskFlag[2]);
////    settings.setValue("TaskFlag3", play->taskFlag[3]);

////    settings.setValue("UpFlag1", play->upFlag[1]);
////    settings.setValue("UpFlag2", play->upFlag[2]);
////    settings.setValue("UpFlag3", play->upFlag[3]);
///
////    QMap<int, int> map1;
////    for (auto it = play->map->gridMap.begin(); it != play->map->gridMap.end(); ++it) {
////        map1[it.key().x*100+it.key().y] = it.value();
////    }
////    QVariant mapVariant = QVariant::fromValue(map1);
////    settings.setValue("GridMap", mapVariant);
////    map1.clear();
////    for (auto it = play->map->mineMap.begin(); it != play->map->mineMap.end(); ++it) {
////        map1[it.key().x*100+it.key().y] = it.value();
////    }
////    mapVariant = QVariant::fromValue(map1);
////    settings.setValue("MineMap", mapVariant);


////    map1.clear();
////    for (auto it = Installations::InstallMap.begin(); it != Installations::InstallMap.end(); ++it) {
////        map1[it.key().x*100+it.key().y] = it.value()->dir;
////    }
////    mapVariant = QVariant::fromValue(map1);
////    settings.setValue("InstallDir", mapVariant);
////    map1.clear();
////    for (auto it = Goods::goodsMap.begin(); it != Goods::goodsMap.end(); ++it) {
////        map1[it.key().x*100+it.key().y] = it.value()->dir;
////    }
////    mapVariant = QVariant::fromValue(map1);
////    settings.setValue("GoodDir", mapVariant);
////    map1.clear();
////    for (auto it = Goods::goodsMap.begin(); it != Goods::goodsMap.end(); ++it) {
////        map1[it.key().x*100+it.key().y] = it.value()->type;
////    }
////    mapVariant = QVariant::fromValue(map1);
////    settings.setValue("GoodType", mapVariant);
//    settings.sync();
//}
