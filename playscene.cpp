#include "playscene.h"

playscene::playscene()
    :drillButton(":/res/mminer.png", ""), beltButton(":/res/belt.png", ""), cutterButton(":/res/cutter0.png", ""), binButton(":/res/trash0.png", ""),coinlabel("Current Coin: 0")
{
    isMousePressed = false;
    setMouseTracking(true);
    createvent = 0;
    imageLabel = new QLabel(this);
    map = new Map(mineUp, mapUp, moneyUp);
//    qDebug()<<"Mapsetted";
    drillButton.move(width()/6, height()-90);
    drillButton.setParent(this);
    beltButton.move(width()/3, height()-90);
    beltButton.setParent(this);
    cutterButton.move(width()/2, height()-90);
    cutterButton.setParent(this);
    binButton.move(width()*2/3, height()-90);
    binButton.setParent(this);
    connect(&drillButton, &mypushbutton::clicked, this, &playscene::drillcreat);
    connect(&beltButton, &mypushbutton::clicked, this, &playscene::beltcreat);
    connect(&cutterButton, &mypushbutton::clicked, this, &playscene::cuttercreat);
    connect(&binButton, &mypushbutton::clicked, this, &playscene::bincreat);
//    this->show();
    imageLabel->setPixmap(QPixmap(":/res/miner.png"));
    imageLabel->hide();
    updatetimer = new QTimer(this);
    connect(updatetimer, &QTimer::timeout, this, [=](){
        update();
    });
    updatetimer->start(20); // 每20毫秒触发一次
    beltTime = new QTimer(this);
    connect(beltTime, &QTimer::timeout, this, [=](){
        qDebug()<<"tomove";
        actrules::calNext(map);
        actrules::moveall(map);
        qDebug()<<"moved";
        qDebug()<<"caled";
    });
    beltspeed = 1000;
    beltTime->start(beltspeed);
    drillerTime = new QTimer(this);
    connect(drillerTime, &QTimer::timeout, this, [=](){
        actrules::produceGoods(map);
    });
    drillerspeed= 1000;
    drillerTime->start(drillerspeed);
    cutterTime = new QTimer(this);
    connect(cutterTime, &QTimer::timeout, this, [=](){
        actrules::cutGoods(map);
    });
    cutterspeed = 1000;
    cutterTime->start(cutterspeed);
    mediaPlaylist.addMedia(QUrl("qrc:/path/to/your/music.mp3"));
    mediaPlayer.setPlaylist(&mediaPlaylist);
    setlabel();
}

void playscene::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    int gridSize = map->gridSize; // 设置格子大小
    QPen grayPen(Qt::gray);
    painter.setPen(grayPen);

    // 绘制地图
    for (int x = 0; x <= width()-90; x += gridSize) {
        painter.drawLine(x, 0, x, height()-90);
    }
    for (int y = 0; y <= height()-90; y += gridSize) {
        painter.drawLine(0, y, width()-90, y);
    }
    //绘制开采物
    for(int x = 0; x <= width()-90-gridSize; x += gridSize)
    {
        for (int y = 0; y <= height()-90-gridSize; y += gridSize){
            position pos = {map->startPos[map->level].x+x/gridSize, map->startPos[map->level].y+y/gridSize};
            if(map->askMine(pos) != 0)
            {
//                qDebug()<<map->askMine({x/30, y/30});
                QPixmap image;
                QRect rect;
                rect.setWidth(gridSize);
                rect.setHeight(gridSize);
                switch (map->askMine(pos)) {
                case 1:
                    image.load(":/res/iron.png");
                    break;
                case 2:
                    image.load(":/res/copper.png");
                }
                painter.drawPixmap(x,y,gridSize,gridSize,image);
            }
        }
    }
    //绘制传送带
    for(int x = 0; x <= width()-120; x += gridSize)
    {
        for (int y = 0; y <= height()-120; y += gridSize){
            position pos = {map->startPos[map->level].x+x/gridSize, map->startPos[map->level].y+y/gridSize};
            if(map->askGrid(pos)==3 && map->askInstall(pos)->type==2)
            {
//                qDebug()<<map->askMine({x/30, y/30});
                Installations* install = map->askInstall(pos);
                QPixmap image;
                if(map->askGrid(install->validIn[1])==3&&map->askInstall(install->validIn[1])->validOut.contains(install->pos)){
                    if(map->askInstall(install->validIn[1])->validOut.contains(install->pos)){
                        qDebug()<<"right";
                        image.load(":/res/belt_top.png");
                    }
                }
                else if(map->askGrid(install->validIn[0])==3&&map->askInstall(install->validIn[0])->validOut.contains(install->pos)){
                    if(map->askInstall(install->validIn[0])->validOut.contains(install->pos)){
                        image.load(":/res/belt_right.png");
                    }
                }
                else if(map->askGrid(install->validIn[2])==3&&map->askInstall(install->validIn[2])->validOut.contains(install->pos)){
                    if(map->askInstall(install->validIn[2])->validOut.contains(install->pos)){
                        image.load(":/res/belt_left.png");
                    }
                }
                else
                    image.load(map->askInstall(pos)->imgpath);
                image = image.scaled(gridSize * map->askInstall(pos)->size_y, gridSize * map->askInstall(pos)->size_x);
                QTransform rotationTransform;
                rotationTransform.rotate(90 * map->askInstall(pos)->dir);
                image = image.transformed(rotationTransform);
                if(map->askInstall(pos)->type == 3 && map->askInstall(pos)->dir == 2){
                    painter.drawPixmap(x - gridSize,y,image);
                }
                else if(map->askInstall(pos)->type == 3 && map->askInstall(pos)->dir == 3){
                    painter.drawPixmap(x,y - gridSize,image);
                }
                else painter.drawPixmap(x,y,image);
            }
        }
    }
    //绘制物品
    if(Goods::goodsMap.empty()==false){
        for (auto it = Goods::goodsMap.begin(); it != Goods::goodsMap.end(); ++it) {
            position pos = it.value()->curpos;
            QPixmap image;
            image.load(it.value()->imgpath);
            image = image.scaled(gridSize*2/3, gridSize*2/3);
            painter.drawPixmap((pos.x - map->startPos[map->level].x) * gridSize+gridSize/6, (pos.y - map->startPos[map->level].y) * gridSize+gridSize/6,image);
        }
    }
    //绘制设备
    for(int x = 0; x <= width()-120; x += gridSize)
    {
        for (int y = 0; y <= height()-120; y += gridSize){
            position pos = {map->startPos[map->level].x+x/gridSize, map->startPos[map->level].y+y/gridSize};
            if(map->askGrid(pos)==3 && map->askInstall(pos)->type!=2)
            {
//                qDebug()<<map->askMine({x/30, y/30});
                QPixmap image;
                image.load(map->askInstall(pos)->imgpath);
                image = image.scaled(gridSize * map->askInstall(pos)->size_y, gridSize * map->askInstall(pos)->size_x);
                QTransform rotationTransform;
                rotationTransform.rotate(90 * map->askInstall(pos)->dir);
                image = image.transformed(rotationTransform);
                if(map->askInstall(pos)->type == 3 && map->askInstall(pos)->dir == 2){
                    painter.drawPixmap(x - gridSize,y,image);
                }
                else if(map->askInstall(pos)->type == 3 && map->askInstall(pos)->dir == 3){
                    painter.drawPixmap(x,y - gridSize,image);
                }
                else painter.drawPixmap(x,y,image);
            }
        }
    }
    //绘制交付中心
//    qDebug()<<map->centPos.x<<' '<<map->centPos.y<<' '<<map->centSize;
    QPixmap image;
    QRect rect;
    rect.setWidth(gridSize * map->centSize);
    rect.setHeight(gridSize * map->centSize);
    image.load(":/res/center_0.png");
    painter.drawPixmap(gridSize * (map->centPos.x - map->startPos[map->level].x) - gridSize/2 ,gridSize * (map->centPos.y - map->startPos[map->level].y) - gridSize/2 , gridSize * (map->centSize+1),gridSize * (map->centSize+1),image);

    //绘制金币

    coinlabel.setText(QString::number(map->coin));
    coinlabel.show();
}
void playscene::setlabel(){
    //金币
    coinlabel.setFont(font);
    coinlabel.setPalette(palette);
    coinlabel.setAlignment(Qt::AlignCenter);
    coinlabel.setText("0");
    coinlabel.setGeometry(width()-90, 0, 90, 90);
    coinlabel.setParent(this);
    coinlabel.show();
}
void playscene::drillcreat(){
    qDebug()<<"drill";
    createvent = 1;
    tmpdir = 0;
    imageLabel->show();
    imageLabel->setPixmap(QPixmap(":/res/miner.png"));
    imageLabel->setScaledContents(true);
    QPoint cursorPos = QCursor::pos();  // 获取全局光标位置
    imageLabel->setGeometry(cursorPos.x() - map->gridSize / 2, cursorPos.y() - map->gridSize / 2, map->gridSize, map->gridSize);
}
void playscene::beltcreat(){
    qDebug()<<"belt";
    createvent = 2;
    tmpdir = 0;
    imageLabel->show();
    imageLabel->setPixmap(QPixmap(":/res/belt_top0.png"));
    imageLabel->setScaledContents(true);
    QPoint cursorPos = QCursor::pos();  // 获取全局光标位置
    imageLabel->setGeometry(cursorPos.x() - map->gridSize / 2, cursorPos.y() - map->gridSize / 2, map->gridSize, map->gridSize);
}
void playscene::cuttercreat(){
    qDebug()<<"belt";
    createvent = 3;
    tmpdir = 0;
    imageLabel->show();
    imageLabel->setPixmap(QPixmap(":/res/cutter.png"));
    imageLabel->setScaledContents(true);
    QPoint cursorPos = QCursor::pos();  // 获取全局光标位置
    imageLabel->setGeometry(cursorPos.x(), cursorPos.y() - map->gridSize / 2, 2 * map->gridSize, map->gridSize);
}
void playscene::bincreat(){
    qDebug()<<"belt";
    createvent = 4;
    tmpdir = 0;
    imageLabel->show();
    imageLabel->setPixmap(QPixmap(":/res/trash.png"));
    imageLabel->setScaledContents(true);
    QPoint cursorPos = QCursor::pos();  // 获取全局光标位置
    imageLabel->setGeometry(cursorPos.x() - map->gridSize / 2, cursorPos.y() - map->gridSize / 2, map->gridSize, map->gridSize);
}
