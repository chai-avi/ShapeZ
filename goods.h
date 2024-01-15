#ifndef GOODS_H
#define GOODS_H

#include "tools.h"
#include<QSet>
class Goods
{
public:
    int type; // 1 iron, 2 copper, 3 halfcopper
    bool cutable; // 0 uncutable others cutable
    QString imgpath;
    position curpos, nextpos;
    bool isStop, acted, moved;
    static QMap<position, Goods*> goodsMap;
    Goods(position pos,int t):type(t){
        curpos = pos;
        goodsMap[pos] = this;
        switch (type) {
        case 1:
            imgpath = ":/res/iron_mine.png";
            cutable = 0;
            break;
        case 2:
            imgpath = ":/res/copper_mine.png";
            cutable = 1;
            break;
        case 3:
            imgpath = ":/res/half_copper_mine.png";
            cutable = 0;
            break;
        }
    }
    ~Goods(){
//        Goods* p = goodsMap[curpos];
        goodsMap.remove(curpos);
        qDebug()<<"unconstructed"<<goodsMap.empty();
    }
};


#endif // GOODS_H
