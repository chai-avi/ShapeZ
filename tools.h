#ifndef TOOLS_H
#define TOOLS_H
//常用工具
#include<QVector>
#include<QMap>
#include <ctime>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QDebug>
#include <QString>
#include <QRect>
#include <QtMath>
#include <random>
#include <ctime>
#include <QIcon>
#include <QPushButton>
#include"config.h"
#include <QDebug>

struct position{
    int x,y;
    position operator+(const position p){
        return {x + p.x, y + p.y};
    }
    bool operator<(const position p) const{
        return x * GAME_HEIGHT + y < p.x * GAME_HEIGHT + p.y;
    }
    bool operator==(const position p) const{
        return x == p.x && y == p.y;
    }
    bool operator!=(const position p) const{
        return *this == p;
    }
    position operator+(const position p) const{
        return {x + p.x, y + p.y};
    }
};
static QMap<int, position> Directions = {{0,{0,-1}},{1,{1,0}},{2,{0,1}},{3,{-1,0}}};

class Tools
{
public:
    Tools();
};

#endif // TOOLS_H
