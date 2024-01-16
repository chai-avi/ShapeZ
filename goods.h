#ifndef GOODS_H
#define GOODS_H

#include "tools.h"
#include<QSet>
class Goods
{
    //开采物
public:
    int type; // 1 iron, 2 copper, 3 halfcopper
    int dir;
    bool cutable; // 0 uncutable others cutable
    QString imgpath;
    position curpos, nextpos;
    bool isStop, acted, moved;
    static QMap<position, Goods*> goodsMap;
    Goods(position pos,int t,int d);
    ~Goods(){
        goodsMap.remove(curpos);
    }
};


#endif // GOODS_H
