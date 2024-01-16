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
    //游戏界面
    Q_OBJECT
private:
    void paintEvent(QPaintEvent *event)override;
    QTimer timer, totaltimer;
    int createvent; //0, 1drill, 2belt, 3cutter, 4bin;
    //ui
    QLabel* imageLabel;
    QLabel coin, coinlabel, good1, good1label, good2, good2label, good3, good3label;
    void setlabel();
    //鼠标事件
    bool isMousePressed;
    int tmpdir;
    //音乐
    QMediaPlayer mediaPlayer;
    QMediaPlaylist mediaPlaylist;
    //局部强化
    int task[4] = {2, 30, 20, 50};
    QLabel Tgood1label, Tgood2label, Tgood3label;
public:
    Map* map;
    mypushbutton drillButton, beltButton, cutterButton, binButton, rotaterButton, musicButton, exitButton, loadButton;
    mypushbutton beltUpButton, drillUpButton, cutterUpButton;
    //计时器
    QTimer *beltTime, *cutterTime, *drillerTime, *updatetimer;
    int beltspeed, cutterspeed, drillerspeed;
    int finishedTask;
    bool taskFlag[4], upFlag[4];
    explicit playscene();
    ~playscene()override{
        Goods::goodsMap.clear();
        Installations::InstallMap.clear();
        delete map;
        delete imageLabel;
        delete beltTime;
        delete cutterTime;
        delete drillerTime;
        delete updatetimer;
    }
protected:
    void mouseMoveEvent(QMouseEvent *event) override {
        // 长按拖动连续放置设备
        QPoint cursorPos = event->pos();
        if (isMousePressed) {
            position curInMap = {map->startPos[map->level].x+cursorPos.x()/map->gridSize, map->startPos[map->level].y+cursorPos.y()/map->gridSize};
            if(map->askGrid(curInMap) == 0 || map->askGrid(curInMap) == 2){
                if(createvent == 3){
                    if(map->askGrid({curInMap.x+Directions[(tmpdir+1)%4].x, curInMap.y+Directions[(tmpdir+1)%4].y}) == 0 || map->askGrid({curInMap.x+Directions[(tmpdir+1)%4].x, curInMap.y+Directions[(tmpdir+1)%4].y}) == 2){
                        map->setInstall(curInMap, createvent, tmpdir);
                    }
                }
                else {
                     map->setInstall(curInMap, createvent, tmpdir);
                }

            }
        }
        // 更新 QLabel 的位置，使其追随鼠标光标
        imageLabel->move(cursorPos.x() - imageLabel->width() / 2, cursorPos.y() - imageLabel->height() / 2);
    }
    void mousePressEvent(QMouseEvent *event) override {
        if (event->button() == Qt::RightButton) {
            // 鼠标右键点击时卸载设备
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
            //鼠标左键点击时放置设备
            QPoint cursorPos = event->pos();
            position curInMap = {map->startPos[map->level].x+cursorPos.x()/map->gridSize, map->startPos[map->level].y+cursorPos.y()/map->gridSize};
            if(map->inMap(curInMap)){
                if(map->askGrid(curInMap) == 0 || map->askGrid(curInMap) == 2){
                    isMousePressed = true;
                    if(createvent == 3){
                        if(map->askGrid({curInMap.x+Directions[(tmpdir+1)%4].x, curInMap.y+Directions[(tmpdir+1)%4].y}) == 0 || map->askGrid({curInMap.x+Directions[(tmpdir+1)%4].x, curInMap.y+Directions[(tmpdir+1)%4].y}) == 2){
                            map->setInstall(curInMap, createvent, tmpdir);
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
            // 当按下 "T" 键时，旋转设备，增加参数 dir 的值
            QPoint cursorPos = QCursor::pos();
            tmpdir++;
            QTransform rotationTransform;
            rotationTransform.rotate(90);
            imageLabel->setGeometry(cursorPos.x() - map->gridSize / 2, cursorPos.y() - map->gridSize / 2, imageLabel->height(), imageLabel->width());
            imageLabel->setPixmap(imageLabel->pixmap()->transformed(rotationTransform));

        }
        else{
            QWidget::keyPressEvent(event);
        }
    }
    void mouseReleaseEvent(QMouseEvent *event) override {
        //点击结束，初始化参数
            isMousePressed = false;
            createvent = 0;
            imageLabel->hide();
        }
signals:

public slots:
    //创建设备
    void drillcreat();
    void beltcreat();
    void cuttercreat();
    void bincreat();
    void rotatercreat();
    void musicEvent();
};

#endif // PLAYSECNE_H
