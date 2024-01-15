#ifndef INSTALLATIONS_H
#define INSTALLATIONS_H

#include "tools.h"
class Installations
{
public:
    int size_x, size_y, type;//type:1.driller 2.belt 3.cutter 4.bin
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
class driller: public Installations
{
public:
    driller(position p, int direction);
    void work();
//    ~driller();
};

class belt: public Installations
{
    static int speed;
public:
    bool good,isWork;
    belt(position p, int direction);

};

class cuter:public Installations
{
public:
    cuter(position p, int direction);
};

class trash:public Installations
{
public:
    trash(position p);
};

#endif // INSTALLATIONS_H
