#include "scenes.h"

scenes::scenes()
{
    this->setFixedSize(GAME_WIDTH, GAME_HEIGHT);
    this->setWindowTitle(GAME_TITLE);
    palette.setColor(QPalette::WindowText, Qt::darkGray);
    font.setPointSize(20);
    font.setBold(true);
    font2.setPointSize(10);
    font2.setBold(true);
}
//初始化全局变量
bool scenes::mineUp=false;
bool scenes::mapUp=false;
bool scenes::moneyUp=false;
int scenes::money=300;
