#ifndef STARTSCENE_H
#define STARTSCENE_H
#include"tools.h"
#include "scenes.h"
#include"mypushbutton.h"
class startscene : public scenes
{
    //开始界面
    Q_OBJECT
private:
    QLabel backgroundLabel;
    QLabel newgameLabel, loadLabel, storeLabel;
public:
    mypushbutton newgameButton, loadButton, storeButton, exitButton;
    explicit startscene();

signals:

public slots:
    void newgame(){}
    void store(){}
    void load(){}
};

#endif // STARTSCENE_H
