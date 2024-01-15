#ifndef ACTRULES_H
#define ACTRULES_H

#include <QObject>
#include"map.h"
#include"goods.h"
#include"tools.h"

class actrules
{
public:
    actrules();
    virtual ~actrules(){}
    static void calNext(Map* mp){
        if(Goods::goodsMap.empty()) return;
        for (auto it = Goods::goodsMap.begin(); it != Goods::goodsMap.end(); ++it) {
//                qDebug() << it.key() << ": " << it.value();
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
//        for (auto it = Goods::goodsMap.begin(); it != Goods::goodsMap.end(); ++it) {
////                qDebug() << it.key() << ": " << it.value();
//            goodNext(it.value(), mp);
//        }
    }
    static void goodNext(Goods* good, Map* mp){
        if(good->acted == true) return;
        if(mp->askGrid(good->curpos) != 3){
//            qDebug()<<"1";
//            good->~Goods();
            good->acted = true;
            good->isStop = true;
            return;
        }
        Installations* install = mp->askInstall(good->curpos);
        if(install->type == 4){
            good->~Goods();
            return;
        }
        for(int i = 0; i < install->validOut.size(); i++){
            if(Goods::goodsMap.contains(install->validOut[i])){
                if(Goods::goodsMap[install->validOut[i]]->acted == false)
                    goodNext(Goods::goodsMap[install->validOut[i]], mp);
            }
        }
        switch (install->type) {        //type:1.driller 2.belt 3.cutter 4.bin
        case 1:
            if(mp->askGrid(install->validOut[0]) != 3){
                if(mp->askGrid(install->validOut[0]) == 1)
                {
                    good->acted = true;
                    good->isStop = false;
                    good->nextpos = install->validOut[0];
                }
                else{
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
        case 2:
            if(mp->askGrid(install->validOut[0]) != 3){
                if(mp->askGrid(install->validOut[0]) == 1)
                {
                    good->acted = true;
                    good->isStop = false;
                    good->nextpos = install->validOut[0];
                }
                else{
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
        case 3:
//            if(good->cutable == false){
//                good->acted = true;
//                good->isStop = true;
//            }
//            else if(mp->askGrid(install->validOut[0]) != 3 || mp->askGrid(install->validOut[1]) != 3){
//                good->acted = true;
//                good->isStop = true;
//            }
//            else if(Goods::goodsMap.contains(install->validOut[0]) && Goods::goodsMap[install->validOut[0]]->isStop == true){
//                good->acted = true;
//                good->isStop = true;
//            }
//            else if(Goods::goodsMap.contains(install->validOut[1]) && Goods::goodsMap[install->validOut[1]]->isStop == true){
//                good->acted = true;
//                good->isStop = true;
//            }
//            else{
//                good->acted = true;
//                good->isStop = false;
//                good->nextpos = install->validOut[0];
//            }
            good->acted = true;
            good->isStop = true;
        }
    }
    static void movegood(Goods* good, Map* mp, QMap<position, Goods*>&tmpGoodmap){
        if(good->moved == true) return;
        if(mp->askGrid(good->curpos) != 3){
            if(mp->askGrid(good->curpos) == 1)
            {
                mp->handedGoods[good->type]++;
                mp->coin+=mp->addcoin;
                good->moved=true;
                qDebug()<<"good++ "<<mp->handedGoods[good->type]<<' '<<good->curpos.x<<' '<<good->curpos.y;
            }
            else{
                good->~Goods();
            }
            qDebug()<<"finish";
            return;
        }
        if(good->isStop == true ){
            tmpGoodmap[good->curpos] = good;
            good->moved = true;
            return;
        }
//        Installations* install = mp->askInstall(good->curpos);
//        if(install->type == 3){
//            good->~Goods();
//            new Goods(install->validOut[0], 3);
//            new Goods(install->validOut[1], 3);
//        }
        if(Goods::goodsMap.contains(good->nextpos) && Goods::goodsMap[good->nextpos]->moved == false){

            movegood(Goods::goodsMap[good->nextpos], mp, tmpGoodmap);
        }
        tmpGoodmap[good->nextpos] = good;
//        tmpGoodmap.remove(good->curpos);
        good->moved = true;
        good->curpos = good->nextpos;
    }
    static void moveall(Map* mp){
        if(Goods::goodsMap.empty()) return;
        for (auto it = Goods::goodsMap.begin(); it != Goods::goodsMap.end(); ++it) {
//                qDebug() << it.key() << ": " << it.value();
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
//        for (auto it = Goods::goodsMap.begin(); it != Goods::goodsMap.end(); ++it) {
//            qDebug()<<it.key().x<<' '<<it.key().y;
//        }
        Goods::goodsMap = tmpMap;
//        for (auto it = Goods::goodsMap.begin(); it != Goods::goodsMap.end(); ++it) {
//            qDebug()<<it.key().x<<' '<<it.key().y;
//        }
//        Goods::goodsMap.clear();
//        for (auto it = tmpMap.begin(); it != tmpMap.end(); ++it) {
//            Goods::goodsMap[it.key()] = it.value();
//            qDebug()<<it.key().x<<' '<<it.key().y;
//        }
//        tmpMap.clear();

    }
    static void produceGoods(Map* mp){
//        for(int i = mp->startPos.x; i < mp->startPos.x + mp->col[mp->level]; i++){
//            for(int j = mp->startPos.y; j < mp->startPos.y + mp->row[mp->level]; j++){
        for(int i =0; i<mp->row[2]; i++){
            for(int j =0; j<mp->col[2]; j++){
                position pos = {i, j};
                if(mp->askGrid(pos)==3 && mp->askInstall(pos)->type==1){
                    if(Goods::goodsMap.contains(pos) == false && mp->askMine(pos)>0){
                        qDebug()<<"new"<<pos.x<<' '<<pos.y;
                        new Goods(pos, mp->askMine(pos));
                    }
                }
            }
        }
    }
    static void cutGoods(Map* mp){
        for(int i =0; i<mp->row[2]; i++){
            for(int j =0; j<mp->col[2]; j++){
                position pos = {i, j};
                if(Goods::goodsMap.contains(pos)){
                    if(mp->askGrid(pos)==3 && mp->askInstall(pos)->type==3 && Goods::goodsMap[pos]->cutable == true){
                        Installations* install = mp->askInstall(pos);
                        if(mp->askGrid(install->validOut[0]) == 3 && mp->askGrid(install->validOut[1]) == 3 && Goods::goodsMap.contains(install->validOut[0]) == false && Goods::goodsMap.contains(install->validOut[1]) == false){
                            Goods::goodsMap[pos]->~Goods();
                            new Goods(install->validOut[0], 3);
                            new Goods(install->validOut[1], 3);
                        }
                    }
                }
            }
        }
//        for (auto it = Goods::goodsMap.begin(); it != Goods::goodsMap.end(); ++it) {

//        }
    }
};

#endif // ACTRULES_H
