#ifndef SHAPEZ_H
#define SHAPEZ_H

#include <QWidget>
#include <QtWidgets>
#include"config.h"
#include"map.h"
#include"installations.h"
#include"goods.h"
#include"tools.h"
#include"scenes.h"
#include"playscene.h"
#include"startscene.h"
#include"mypushbutton.h"
#include"shopscene.h"
namespace Ui {
class ShapeZ;
}

class ShapeZ : public QWidget
{
    Q_OBJECT
private:
    scenes* gamescene;
    playscene* play;
    startscene* start;
    shopscene* shop;
public:
    explicit ShapeZ(QWidget *parent = nullptr);
    ~ShapeZ();
    void  initScene();

private:
    Ui::ShapeZ *ui;
protected:

};

#endif // SHAPEZ_H
