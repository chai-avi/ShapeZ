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
namespace Ui {
class ShapeZ;
}

class ShapeZ : public QWidget
{
    Q_OBJECT
//    Map* map;
public:
    explicit ShapeZ(QWidget *parent = nullptr);
    ~ShapeZ();
    void  initScene();

private:
    Ui::ShapeZ *ui;
protected:
//    void paintEvent(QPaintEvent *event) override {
//        QPainter painter(this);
//        painter.setRenderHint(QPainter::Antialiasing, true);

//        int gridSize = 30; // 设置格子大小
//        QPen grayPen(Qt::gray);
//        painter.setPen(grayPen);

//        // 绘制竖线
//        for (int x = 0; x <= width()-120; x += gridSize) {
//            painter.drawLine(x, 0, x, height()-120);
//        }

//        // 绘制横线
//        for (int y = 0; y <= height()-120; y += gridSize) {
//            painter.drawLine(0, y, width()-120, y);
//        }

//        for(int x = 0; x <= width()-120; x += gridSize)
//        {
//            for (int y = 0; y <= height()-120; y += gridSize){
//                if(map->askGrid({x/30, y/30})==1)
//                {
//                    QPixmap image;
//                    QRect rect;
//                    rect.setWidth(30);
//                    rect.setHeight(30);
//                    image.load(":/res/clubs.png");
//                    painter.drawPixmap(x,y,30,30,image);
//                }
//            }
//        }
//    }
};

#endif // SHAPEZ_H
