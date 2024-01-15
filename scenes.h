#ifndef SCENES_H
#define SCENES_H

#include <QObject>
#include <QWidget>
#include"tools.h"
#include"map.h"
#include <QFontDatabase>

class scenes : public QWidget
{
    Q_OBJECT
public:
    static bool mineUp, mapUp, moneyUp;
    static int money;
    explicit scenes();
//    QPushButton back;
//    void backSet();
    QFont font;
    QPalette palette;
signals:

public slots:
};

#endif // SCENES_H
