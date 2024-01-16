#ifndef SCENES_H
#define SCENES_H

#include <QObject>
#include <QWidget>
#include"tools.h"
#include"map.h"
#include <QFontDatabase>

class scenes : public QWidget
{
    //界面类
    Q_OBJECT
public:
    //全局变量
    static bool mineUp, mapUp, moneyUp;
    static int money;
    explicit scenes();
    QFont font, font2;
    QPalette palette;
signals:

public slots:
};

#endif // SCENES_H
