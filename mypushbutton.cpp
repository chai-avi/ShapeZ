#include "mypushbutton.h"

mypushbutton::mypushbutton(QString img, QString clkImg)
{
    imgpath = img;
    clkImgpath = clkImg;
    QPixmap pix;
    pix.load(imgpath);

    this->setFixedSize(90,90);
    this->setStyleSheet("QPushButton{border:0px}");
    this->setIcon(pix);
    this->setIconSize(QSize(90,90));
}
