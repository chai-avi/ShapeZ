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
    static void calNext(Map* mp);
    static void goodNext(Goods* good, Map* mp);

    static void movegood(Goods* good, Map* mp, QMap<position, Goods*>&tmpGoodmap);
    static void moveall(Map* mp);

    static void produceGoods(Map* mp);
    static void cutGoods(Map* mp);
};

#endif // ACTRULES_H
