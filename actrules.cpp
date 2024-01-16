#include "actrules.h"


actrules::actrules()
{
}
void actrules::calNext(Map* mp){//计算所有开采物下一时刻位置
    if(Goods::goodsMap.empty()) return;
    for (auto it = Goods::goodsMap.begin(); it != Goods::goodsMap.end(); ++it) {
        it.value()->acted = false;
    }
    for(int i =0; i<mp->row[2]; i++){
        for(int j =0; j<mp->col[2]; j++){
            position pos = {i, j};
            if(Goods::goodsMap.contains(pos)){
                goodNext(Goods::goodsMap[pos], mp);
            }
        }
    }
}
void actrules::goodNext(Goods* good, Map* mp){//计算一个开采物下一时刻位置
    if(good->acted == true) return;
    if(mp->askGrid(good->curpos) != 3){
        good->nextpos = good->curpos;
        good->acted = true;
        good->isStop = true;
        return;
    }
    Installations* install = mp->askInstall(good->curpos);
    if(install->type == 4){//垃圾桶
        good->~Goods();
        return;
    }
    for(int i = 0; i < install->validOut.size(); i++){
        if(Goods::goodsMap.contains(install->validOut[i])){
            if(Goods::goodsMap[install->validOut[i]]->acted == false)
                goodNext(Goods::goodsMap[install->validOut[i]], mp);
        }
    }
    //不同设备中下一时刻的情况
    switch (install->type) {
    case 1://开采器
        if(mp->askGrid(install->validOut[0]) != 3){
            if(mp->askGrid(install->validOut[0]) == 1)
            {
                good->acted = true;
                good->isStop = false;
                good->nextpos = install->validOut[0];
            }
            else{
                good->nextpos = good->curpos;
                good->acted = true;
                good->isStop = true;
            }
        }
        else if(Goods::goodsMap.contains(install->validOut[0])){
            if(Goods::goodsMap[install->validOut[0]]->isStop == false){
                good->acted = true;
                good->isStop = false;
                good->nextpos = install->validOut[0];
            }
            else{
                good->nextpos = good->curpos;
                good->acted = true;
                good->isStop = true;
            }
        }
        else{
            good->acted = true;
            good->isStop = false;
            good->nextpos = install->validOut[0];
        }
        break;
    case 2://传送带
        if(mp->askGrid(install->validOut[0]) != 3){
            if(mp->askGrid(install->validOut[0]) == 1)
            {
                good->acted = true;
                good->isStop = false;
                good->nextpos = install->validOut[0];
            }
            else{
                good->nextpos = good->curpos;
                good->acted = true;
                good->isStop = true;
            }
        }
        else if(Goods::goodsMap.contains(install->validOut[0])){
            if(Goods::goodsMap[install->validOut[0]]->isStop == false){
                good->acted = true;
                good->isStop = false;
                good->nextpos = install->validOut[0];
            }
            else{
                good->nextpos = good->curpos;
                good->acted = true;
                good->isStop = true;
            }
        }
        else{
            good->acted = true;
            good->isStop = false;
            good->nextpos = install->validOut[0];
        }
        break;
    case 3://切割机
        good->nextpos = good->curpos;
        good->acted = true;
        good->isStop = true;
        break;
    case 5://旋转器
        if(mp->askGrid(install->validOut[0]) != 3){
            if(mp->askGrid(install->validOut[0]) == 1)
            {
                good->acted = true;
                good->isStop = false;
                good->nextpos = install->validOut[0];
                good->dir = (good->dir+1)%4;
            }
            else{
                good->nextpos = good->curpos;
                good->acted = true;
                good->isStop = true;
            }
        }
        else if(Goods::goodsMap.contains(install->validOut[0])){
            if(Goods::goodsMap[install->validOut[0]]->isStop == false){
                good->acted = true;
                good->isStop = false;
                good->nextpos = install->validOut[0];
                good->dir = (good->dir+1)%4;
            }
            else{
                good->nextpos = good->curpos;
                good->acted = true;
                good->isStop = true;
            }
        }
        else{
            good->dir = (good->dir+1)%4;
            good->acted = true;
            good->isStop = false;
            good->nextpos = install->validOut[0];
        }
        break;
    }
}
void actrules::movegood(Goods* good, Map* mp, QMap<position, Goods*>&tmpGoodmap){
    //移动一个开采物
    if(good->moved == true) return;
    if(mp->askGrid(good->curpos) != 3){
        if(mp->askGrid(good->curpos) == 1)
        {
            mp->handedGoods[good->type]++;
            mp->coin+=mp->addcoin;
            good->moved=true;
        }
        else{
            good->~Goods();
        }
        return;
    }
    if(good->isStop == true ){
        tmpGoodmap[good->curpos] = good;
        good->moved = true;
        return;
    }
    if(Goods::goodsMap.contains(good->nextpos) && Goods::goodsMap[good->nextpos]->moved == false){
        movegood(Goods::goodsMap[good->nextpos], mp, tmpGoodmap);
    }
    tmpGoodmap[good->nextpos] = good;
    good->moved = true;
    good->curpos = good->nextpos;
}
void actrules::moveall(Map* mp){
    //移动所有开采物
    if(Goods::goodsMap.empty()) return;
    for (auto it = Goods::goodsMap.begin(); it != Goods::goodsMap.end(); ++it) {
        it.value()->moved = false;
    }
    QMap<position, Goods*> tmpMap;
    for(int i =0; i<mp->row[2]; i++){
        for(int j =0; j<mp->col[2]; j++){
            position pos = {i, j};
            if(Goods::goodsMap.contains(pos)){
                movegood(Goods::goodsMap[pos], mp, tmpMap);
            }
        }
    }
    Goods::goodsMap = tmpMap;
}
void actrules:: produceGoods(Map* mp){
    //开采器生成新的开采物
    for(int i =0; i<mp->row[2]; i++){
        for(int j =0; j<mp->col[2]; j++){
            position pos = {i, j};
            if(mp->askGrid(pos)==3 && mp->askInstall(pos)->type==1){
                if(Goods::goodsMap.contains(pos) == false && mp->askMine(pos)>0){
                    new Goods(pos, mp->askMine(pos), 0);
                }
            }
        }
    }
}
void actrules:: cutGoods(Map* mp){
    //切割机工作
    for(int i =0; i<mp->row[2]; i++){
        for(int j =0; j<mp->col[2]; j++){
            position pos = {i, j};
            if(Goods::goodsMap.contains(pos)){
                if(mp->askGrid(pos)==3 && mp->askInstall(pos)->type==3 && Goods::goodsMap[pos]->cutable == true){
                    Installations* install = mp->askInstall(pos);
                    if(mp->askGrid(install->validOut[0]) == 3 && mp->askGrid(install->validOut[1]) == 3 && Goods::goodsMap.contains(install->validOut[0]) == false && Goods::goodsMap.contains(install->validOut[1]) == false){
                        Goods::goodsMap[pos]->~Goods();
                        new Goods(install->validOut[0], 3, 0);
                        new Goods(install->validOut[1], 3, 2);
                    }
                }
            }
        }
    }
}
