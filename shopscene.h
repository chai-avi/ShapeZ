#ifndef SHOPSCENE_H
#define SHOPSCENE_H
#include"tools.h"
#include "scenes.h"
#include"mypushbutton.h"

class shopscene : public scenes
{
    //商店界面
    Q_OBJECT
private:
    QLabel storeLabel, mapLabel, mineLabel, moneyLabel, coin;
public:
    QLabel coinlabel;
    mypushbutton mapButton, mineButton, moneyButton, exitButton;
    explicit shopscene();

signals:

public slots:
};

#endif // SHOPSCENE_H
