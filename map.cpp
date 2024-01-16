#include "map.h"

void Map::setCenter(){//设置交付中心
    centSize = 4;
    centPos = {row[2]/2-2, col[2]/2-2};
    for(int i = 0; i < centSize; i++)
        for(int j = 0; j < centSize; j++)
            gridMap[{i + centPos.x, j + centPos.y}] = 1;
}
void Map::addMine(int sum){//生成随机地图
    srand(time(0));
    for(; sum > 0; sum--){
        int mineType = rand() % mineNum + 1;
        position start = {rand() % row[2], rand() % col[2]};
        mineMap[start] = mineType;
        gridMap[start] = 2;
        int steps = 10; // 控制移动步数
        for (int i = 0; i < steps; ++i) {
            int dir = rand() % 4; // 随机选择方向
            position newDir = {Directions[dir].x + start.x, Directions[dir].y + start.y};
            if (inMap(newDir) && askGrid(newDir) != 1&& askGrid(newDir) != 2) {
                start = newDir;
                mineMap[start] = mineType;
                gridMap[start] = 2;
            }
        }
    }
}

void Map::setRandMine(int sum){
    addMine(sum);
}
Map::Map(int money, bool mineUp, bool mapUp, bool moneyUp){
    for (int i=0; i<=4; i++) {
        handedGoods[i] = 0;
    }
    gridSize = 100;
    coin = money;
    addcoin = 1;
    mineNum = 2; level = 0;
    for (int i = 0; i < row[2]; i++) {
        for (int j = 0; j < row[2]; j++) {
            gridMap[{i, j}] = 0;
            mineMap[{i, j}] = 0;

        }
    }
    levelUp();
    setRandMine(30);
    setCenter();
    if(mineUp){
        addMine(60);
    }
    if(mapUp){
        levelUp();
    }
    if(moneyUp){
        addcoin = 2;
    }
}
