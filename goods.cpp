#include "goods.h"
QMap<position, Goods*> Goods:: goodsMap;
Goods::Goods(position pos,int t,int d):type(t),dir(d){
    curpos = pos;
    nextpos = pos;
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
    isStop=true; acted = false; moved = false;
}
