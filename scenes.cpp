#include "scenes.h"

scenes::scenes()
{
    mineUp=false; mapUp=false; moneyUp=false;
    this->setFixedSize(GAME_WIDTH, GAME_HEIGHT);
    this->setWindowTitle(GAME_TITLE);
    backSet();
    palette.setColor(QPalette::WindowText, Qt::darkGray);
    font.setPointSize(20);
    font.setBold(true);
//    this->show();
}
void scenes::backSet()
{
    back.setParent(this);
    back.move(GAME_WIDTH - 250, GAME_HEIGHT - 150);
    back.setFixedSize(200, 80);
    back.setStyleSheet("QPushButton{border-image: url(:/buttons/back.png)}");
}
