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
    setFixedSize(GAME_WIDTH+120,GAME_HEIGHT+120);
        //设置窗口标题
    setWindowTitle(GAME_TITLE);
//    scenes* scene = new scenes();
//    scene->show();
    startscene* scene2 = new startscene();
//    qDebug()<<"show";
    scene2->show();
//    delete scene2;
//    this->show();
}
