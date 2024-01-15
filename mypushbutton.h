#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H
#include <QPushButton>
#include<QString>

class mypushbutton: public QPushButton
{
    Q_OBJECT
public:
    mypushbutton(QString img, QString clkImg);
    QString imgpath, clkImgpath;
};

#endif // MYPUSHBUTTON_H
