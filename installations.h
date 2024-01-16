#ifndef INSTALLATIONS_H
#define INSTALLATIONS_H

#include "tools.h"
class Installations
{
    //设备
public:
    int size_x, size_y, type;//type:1.driller 2.belt 3.cutter 4.bin 5rotater
    position pos;
    int dir;
    QVector<position> validIn, validOut;
    bool iswork;
    static QMap<position, Installations*> InstallMap;
    Installations(position p):pos(p),iswork(1){}
    Installations(){
        type = 0;
    }
    void uninstall();
    ~Installations(){
        uninstall();
    }
    QString imgpath;
};
//开采器
class driller: public Installations
{
public:
    driller(position p, int direction);
};
//传送带
class belt: public Installations
{
public:
    belt(position p, int direction);

};
//切割机
class cuter:public Installations
{
public:
    cuter(position p, int direction);
};
//垃圾桶
class trash:public Installations
{
public:
    trash(position p);
};
//旋转器
class rotater:public Installations
{
public:
    rotater(position p, int direction);
};
#endif // INSTALLATIONS_H
