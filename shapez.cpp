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
        //设置窗口标题
    setWindowTitle(GAME_TITLE);
    gamescene = new scenes();
    start = new startscene();
    shop = new shopscene;
    start->show();
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
}
