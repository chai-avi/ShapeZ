#ifndef MAP_H
#define MAP_H
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QMouseEvent>
#include "tools.h"
#include "installations.h"
class Map: public QGraphicsRectItem
{
private:
    void setRandMine(int sum);
    void setCenter();
public:
    QMap<position, int> gridMap;//-1invalid, 0 empty, 1 center, 2 mine, 3 installation
    QMap<position, int> mineMap;
    int level,mineNum;
    int col[3]={12, 20, 40}, row[3]={21, 35, 70};
    position startPos[3] = {{25, 14},{17,10},{0,0}};
    int gridSize;
    position centPos;
    int centSize;
    int coin;
    int addcoin;
    int handedGoods[5];
    bool inMap(position pos) {
        return pos.x >= 0 && pos.x < row[2] && pos.y >= 0 && pos.y < col[2];
    }
    Map(){}
    Map(int money, bool mineUp, bool mapUp, bool moneyUp);
    int askGrid(position pos){
        return gridMap[pos];
    }
    int askMine(position pos){
        return mineMap[pos];
    }
    Installations* askInstall(position pos){
        return Installations::InstallMap[pos];
    }
    void setInstall(position pos, int type, int dir){//在地图上放置设备
        setGrid(pos, 3);
        if(type == 3){
        setGrid({pos.x+Directions[(dir+1)%4].x, pos.y+Directions[(dir+1)%4].y}, -1);
        }
        Installations* i;
        switch (type) {
        case 1:
            i = new driller(pos, dir);
            break;
        case 2:
            i = new belt(pos, dir);
            break;
        case 3:
            i = new cuter(pos, dir);
            break;
        case 4:
            i = new trash(pos);
            break;
        case 5:
            i = new rotater(pos, dir);
            break;
        }
    }
    void setGrid(position pos, int x){//设置地图
        gridMap[pos] = x;
    }
    void unInstall(position pos){//卸载设备
        if(askGrid(pos) == 3){
            Installations* p = Installations::InstallMap[pos];
            if(askInstall(pos)->type == 3){
                position nextpos = {pos.x + Directions[(p->dir+1)%4].x, pos.y + Directions[(p->dir+1)%4].y};
                setGrid(nextpos, 0);
                Installations::InstallMap.remove(nextpos);
            }
            Installations::InstallMap.remove(pos);
        }
        if(mineMap[pos]!=0) gridMap[pos] = 2;
        else gridMap[pos] = 0;
    }
    void addMine(int sum);
    void levelUp(){//地图升级
        if(level>=2) return;
        level++;
        if(level==1) gridSize = 60;
        else gridSize =30;
        
    }
};

#endif // MAP_H
