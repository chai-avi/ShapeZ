#ifndef PLAYSECNE_H
#define PLAYSECNE_H
#include"tools.h"
#include"scenes.h"
#include <QTimer>
#include<QVBoxLayout>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "mypushbutton.h"
#include "installations.h"
#include"actrules.h"

class playscene :  public scenes
{
    Q_OBJECT
private:
    void paintEvent(QPaintEvent *event)override;
    QTimer timer, totaltimer;
    int createvent; //0, 1drill, 2belt, 3cutter, 4bin;
    QLabel* imageLabel;
    QLabel coin, coinlabel, good1, good1label, good2, good2label, good3, good3label;
    bool isMousePressed;
    int tmpdir;
    int beltspeed, cutterspeed, drillerspeed;
    QTimer *beltTime, *cutterTime, *drillerTime, *updatetimer;
    QMediaPlayer mediaPlayer;
    QMediaPlaylist mediaPlaylist;
    void setlabel();

public:
    Map* map;
    mypushbutton drillButton, beltButton, cutterButton, binButton, rotaterButton, musicButton, exitButton;
    explicit playscene();
    ~playscene()override{
        Goods::goodsMap.clear();
        delete map;
        delete imageLabel;
        delete beltTime;
        delete cutterTime;
        delete drillerTime;
        delete updatetimer;
    }
protected:
    void mouseMoveEvent(QMouseEvent *event) override {
        // 获取鼠标当前位置
        QPoint cursorPos = event->pos();
        if (isMousePressed) {
            position curInMap = {map->startPos[map->level].x+cursorPos.x()/map->gridSize, map->startPos[map->level].y+cursorPos.y()/map->gridSize};
            if(map->askGrid(curInMap) == 0 || map->askGrid(curInMap) == 2){
                if(createvent == 3){
                    if(map->askGrid({curInMap.x+Directions[(tmpdir+1)%4].x, curInMap.y+Directions[(tmpdir+1)%4].y}) == 0 || map->askGrid({curInMap.x+Directions[(tmpdir+1)%4].x, curInMap.y+Directions[(tmpdir+1)%4].y}) == 2){
                        map->setInstall(curInMap, createvent, tmpdir);
                        qDebug()<<curInMap.x+Directions[(tmpdir+1)%4].x<<' '<<curInMap.y+Directions[(tmpdir+1)%4].y<<' '<<map->askGrid({curInMap.x+Directions[(tmpdir+1)%4].x, curInMap.y+Directions[(tmpdir+1)%4].y});
                    }
                }
                else {
                     map->setInstall(curInMap, createvent, tmpdir);
                }

            }
        }
        // 更新 QLabel 的位置，使其追随鼠标光标
        imageLabel->move(cursorPos.x() - imageLabel->width() / 2, cursorPos.y() - imageLabel->height() / 2);
//        update();
    }
    void mousePressEvent(QMouseEvent *event) override {
        if (event->button() == Qt::RightButton) {
                    // 在鼠标右键点击时执行的操作
            qDebug() << "Right mouse button pressed at: " << event->pos();
            QPoint cursorPos = event->pos();
            position curInMap = {map->startPos[map->level].x+cursorPos.x()/map->gridSize, map->startPos[map->level].y+cursorPos.y()/map->gridSize};
            if(map->inMap(curInMap)){
                if(map->askGrid(curInMap) == 3)
                    map->unInstall(curInMap);
                else if(map->askGrid(curInMap) == -1){
                    int dir = map->askInstall(curInMap)->dir - 1;
                    if(dir<0) dir += 4;
                    map->unInstall({curInMap.x+Directions[dir].x, curInMap.y+Directions[dir].y});
                }
            }

        }
        else if(createvent != 0)
            {
                QPoint cursorPos = event->pos();
                position curInMap = {map->startPos[map->level].x+cursorPos.x()/map->gridSize, map->startPos[map->level].y+cursorPos.y()/map->gridSize};
                qDebug() << "Left mouse button pressed at: " << event->pos();
                qDebug()<<curInMap.x<<' '<<curInMap.y;
                if(map->inMap(curInMap)){
                    if(map->askGrid(curInMap) == 0 || map->askGrid(curInMap) == 2){
                        isMousePressed = true;
                        if(createvent == 3){
                            if(map->askGrid({curInMap.x+Directions[(tmpdir+1)%4].x, curInMap.y+Directions[(tmpdir+1)%4].y}) == 0 || map->askGrid({curInMap.x+Directions[(tmpdir+1)%4].x, curInMap.y+Directions[(tmpdir+1)%4].y}) == 2){
                                map->setInstall(curInMap, createvent, tmpdir);
                                qDebug()<<curInMap.x+Directions[(tmpdir+1)%4].x<<' '<<curInMap.y+Directions[(tmpdir+1)%4].y<<' '<<map->askGrid({curInMap.x+Directions[(tmpdir+1)%4].x, curInMap.y+Directions[(tmpdir+1)%4].y});
                            }
                        }
                        else {
                            map->setInstall(curInMap, createvent, tmpdir);
                        }

                    }
                }
            }


        else{
            tmpdir = 0;
            QWidget::mousePressEvent(event);
        }
    }
    void keyPressEvent(QKeyEvent *event) override {
        if (event->key() == Qt::Key_T) {
            // 当按下 "T" 键时，增加参数 dir 的值
            QPoint cursorPos = QCursor::pos();
            tmpdir++;
            qDebug() << "T key pressed. dir = " << tmpdir;
            QTransform rotationTransform;
            rotationTransform.rotate(90);
//            imageLabel->setFixedSize(imageLabel->height(), imageLabel->width());
            imageLabel->setGeometry(cursorPos.x() - map->gridSize / 2, cursorPos.y() - map->gridSize / 2, imageLabel->height(), imageLabel->width());
            imageLabel->setPixmap(imageLabel->pixmap()->transformed(rotationTransform));

        }
        else{
            QWidget::keyPressEvent(event);
        }
    }
    void mouseReleaseEvent(QMouseEvent *event) override {
//            if (event->button() == Qt::LeftButton) {
                // 在释放处执行操作
                // 例如，可以在这里添加你的释放操作逻辑
                qDebug() << "Left mouse button released at: " << event->pos();
                isMousePressed = false;
                createvent = 0;
                imageLabel->hide();
//            }
        }
signals:

public slots:
    void drillcreat();
    void beltcreat();
    void cuttercreat();
    void bincreat();
    void rotatercreat();
    void musicEvent();
    void exitEvent();
    void timeStart(){
        beltTime->start(beltspeed);
        cutterTime->start(cutterspeed);
        drillerTime->start(drillerspeed);
//        updatetimer->start();
    }
    void timeStop(){
        beltTime->stop();
        cutterTime->stop();
        drillerTime->stop();
//        updatetimer->start();
    }
};

#endif // PLAYSECNE_H
