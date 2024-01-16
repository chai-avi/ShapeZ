#include "playscene.h"

playscene::playscene()
    :drillButton(":/res/mminer.png", ""), beltButton(":/res/belt.png", ""), cutterButton(":/res/cutter0.png", ""),
      binButton(":/res/trash0.png", ""), musicButton(":/res/music_on.png", ":/res/music_off.png"),
      exitButton(":/res/exit.png", ""), rotaterButton(":/res/rotater.png", ""), loadButton(":/res/save.png",""), beltUpButton(":/res/belt_top.png", ":/res/belt_top0.png"),
      drillUpButton(":/res/miner0.png", ":/res/miner.png"),cutterUpButton(":/res/ccutter.png", ":/res/cutter.png")
{
    isMousePressed = false;
    setMouseTracking(true);
    createvent = 0;
    imageLabel = new QLabel(this);
    //使用全局变量初始化地图
    map = new Map(money, mineUp, mapUp, moneyUp);
    //页面布局
    drillButton.move(width()/6, height()-90);
    drillButton.setParent(this);
    beltButton.move(width()/3, height()-90);
    beltButton.setParent(this);
    cutterButton.move(width()/2, height()-90);
    cutterButton.setParent(this);
    binButton.move(width()*2/3, height()-90);
    binButton.setParent(this);
    rotaterButton.move(width()*5/6, height()-90);
    rotaterButton.setParent(this);
    //连接按钮和槽函数
    connect(&drillButton, &mypushbutton::clicked, this, &playscene::drillcreat);
    connect(&beltButton, &mypushbutton::clicked, this, &playscene::beltcreat);
    connect(&cutterButton, &mypushbutton::clicked, this, &playscene::cuttercreat);
    connect(&binButton, &mypushbutton::clicked, this, &playscene::bincreat);
    connect(&rotaterButton, &mypushbutton::clicked, this, &playscene::rotatercreat);
    //局部升级
    drillUpButton.setIconSize(QSize(45,45));
    drillUpButton.move(width()- 90, height()-450);
    drillUpButton.setParent(this);
    beltUpButton.setIconSize(QSize(45,45));
    beltUpButton.move(width()- 90, height()-360);
    beltUpButton.setParent(this);
    cutterUpButton.move(width()- 90, height()-270);
    cutterUpButton.setParent(this);
    connect(&drillUpButton, &mypushbutton::clicked, this, [=](){
        if(finishedTask > 0 && upFlag[1] == false){
            finishedTask --;
            upFlag[1] = true;
            drillerspeed = 1000;
            drillerTime->start(drillerspeed);
        }
    });
    connect(&beltUpButton, &mypushbutton::clicked, this, [=](){
        if(finishedTask > 0 && upFlag[2] == false){
            finishedTask --;
            upFlag[2] = true;
            beltspeed = 500;
            beltTime->start(beltspeed);
        }
    });
    connect(&cutterUpButton, &mypushbutton::clicked, this, [=](){
        if(finishedTask > 0 && upFlag[3] == false){
            finishedTask --;
            upFlag[3] = true;
            cutterspeed = 1000;
            cutterTime->start(cutterspeed);
        }
    });
    //音乐初始化
    mediaPlaylist.addMedia(QUrl("qrc:/res/music.mp3"));
    mediaPlaylist.setPlaybackMode(QMediaPlaylist::Loop);
    mediaPlayer.setPlaylist(&mediaPlaylist);
    mediaPlayer.play();
    musicButton.move(width()- 90, height()-180);
    musicButton.setParent(this);
    connect(&musicButton, &mypushbutton::clicked, this, &playscene::musicEvent);
    //退出键
    exitButton.move(width()- 90, height()-90);
    exitButton.setIconSize(QSize(70,70));
    exitButton.setParent(this);
    //存档键
    loadButton.move(width()- 180, height()-90);
    loadButton.setIconSize(QSize(70,70));
    loadButton.setParent(this);
    imageLabel->setPixmap(QPixmap(":/res/miner.png"));
    imageLabel->hide();
    //计时器
    updatetimer = new QTimer(this);
    connect(updatetimer, &QTimer::timeout, this, [=](){
        update();
    });
    updatetimer->start(100);
    beltTime = new QTimer(this);
    connect(beltTime, &QTimer::timeout, this, [=](){
        qDebug()<<"tomove";
        actrules::moveall(map);
        actrules::calNext(map);
        for(int i = 1; i <= 3; i++)
        {
            if(taskFlag[i] == false && map->handedGoods[i] >= task[i]){
                finishedTask++;
                taskFlag[i] = true;
            }
        }
        qDebug()<<"moved";
        qDebug()<<"caled";
    });
    beltspeed = 900;
    beltTime->start(beltspeed);
    drillerTime = new QTimer(this);
    connect(drillerTime, &QTimer::timeout, this, [=](){
        actrules::produceGoods(map);
    });
    drillerspeed= 3000;
    drillerTime->start(drillerspeed);
    cutterTime = new QTimer(this);
    connect(cutterTime, &QTimer::timeout, this, [=](){
        actrules::cutGoods(map);
    });
    cutterspeed = 3000;
    cutterTime->start(cutterspeed);
    //标签ui
    setlabel();
    //任务设置
    for(int i = 1; i <= 3; i++){
        taskFlag[i] = false;
        upFlag[i] = false;
    }
    finishedTask = 0;

}

void playscene::paintEvent(QPaintEvent *event) {//绘图函数
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    int gridSize = map->gridSize;
    QPen grayPen(Qt::gray);
    painter.setPen(grayPen);
    // 绘制地图格子
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
                Installations* install = map->askInstall(pos);
                QPixmap image;
                //不同方向的传送带加载不同图片
                if(map->askGrid(install->validIn[1])==3&&map->askInstall(install->validIn[1])->validOut.contains(install->pos)){
                    if(map->askInstall(install->validIn[1])->validOut.contains(install->pos)){
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
                //旋转方向
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
            position dir = {it.value()->nextpos.x - it.value()->curpos.x, it.value()->nextpos.y - it.value()->curpos.y};
            int time = beltspeed - beltTime->remainingTime();
            QPixmap image;
            image.load(it.value()->imgpath);
            image = image.scaled(gridSize*2/3, gridSize*2/3);
            QTransform rotationTransform;
            rotationTransform.rotate(90 * it.value()->dir);
            image = image.transformed(rotationTransform);
            painter.drawPixmap((pos.x - map->startPos[map->level].x) * gridSize + gridSize/6 + dir.x*time*gridSize/beltspeed, (pos.y - map->startPos[map->level].y) * gridSize+gridSize/6+ dir.y*time*gridSize/beltspeed,image);
        }
    }
    //绘制设备(除传送带）
    for(int x = 0; x <= width()-120; x += gridSize)
    {
        for (int y = 0; y <= height()-120; y += gridSize){
            position pos = {map->startPos[map->level].x+x/gridSize, map->startPos[map->level].y+y/gridSize};
            if(map->askGrid(pos)==3 && map->askInstall(pos)->type!=2)
            {
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
    QPixmap image;
    image.load(":/res/center_0.png");
    painter.drawPixmap(gridSize * (map->centPos.x - map->startPos[map->level].x) - gridSize/2 ,gridSize * (map->centPos.y - map->startPos[map->level].y) - gridSize/2 , gridSize * (map->centSize+1),gridSize * (map->centSize+1),image);
    //绘制交付中心显示的任务
    image.load(":/res/copper_mine.png");
    painter.drawPixmap(gridSize * (map->centPos.x - map->startPos[map->level].x) + gridSize/2, gridSize * (map->centPos.y - map->startPos[map->level].y + 1) - gridSize/2, gridSize, gridSize, image);
    image.load(":/res/iron_mine.png");
    painter.drawPixmap(gridSize * (map->centPos.x - map->startPos[map->level].x) + gridSize/2, gridSize * (map->centPos.y - map->startPos[map->level].y + 2) - gridSize/2, gridSize, gridSize, image);
    image.load(":/res/half_copper_mine.png");
    painter.drawPixmap(gridSize * (map->centPos.x - map->startPos[map->level].x) + gridSize/2, gridSize * (map->centPos.y - map->startPos[map->level].y + 3) - gridSize/2, gridSize, gridSize, image);
    if(map->handedGoods[1]<=task[1])
        Tgood1label.setText(QString::number(map->handedGoods[1])+"/"+QString::number(task[1]));
    else
        Tgood1label.setText("Done");
    if(map->handedGoods[2]<=task[2])
        Tgood2label.setText(QString::number(map->handedGoods[2])+"/"+QString::number(task[2]));
    else
        Tgood2label.setText("Done");
    if(map->handedGoods[3]<=task[3])
        Tgood3label.setText(QString::number(map->handedGoods[3])+"/"+QString::number(task[3]));
    else
        Tgood3label.setText("Done");
    //绘制金币
    coinlabel.setText(QString::number(map->coin));
    good1label.setText(QString::number(map->handedGoods[1]));
    good2label.setText(QString::number(map->handedGoods[2]));
    good3label.setText(QString::number(map->handedGoods[3]));
    //局部强化
    QPixmap pix;
    if(upFlag[1] == true){//开采器
        pix.load(":/res/savegame_correct");
        drillUpButton.setIcon(pix);
    }
    else{
        if(finishedTask >0){
            pix.load(drillUpButton.clkImgpath);
            drillUpButton.setIcon(pix);
        }
        else{
            pix.load(drillUpButton.imgpath);
            drillUpButton.setIcon(pix);
        }
    }
    if(upFlag[2] == true){//传送带
        pix.load(":/res/savegame_correct");
        beltUpButton.setIcon(pix);
    }
    else{
        if(finishedTask >0){
            pix.load(beltUpButton.clkImgpath);
            beltUpButton.setIcon(pix);
        }
        else{
            pix.load(beltUpButton.imgpath);
            beltUpButton.setIcon(pix);
        }
    }
    if(upFlag[3] == true){//切割器
        pix.load(":/res/savegame_correct");
        cutterUpButton.setIcon(pix);
        cutterUpButton.setIconSize(QSize(45,45));
    }
    else{
        if(finishedTask >0){
            pix.load(cutterUpButton.clkImgpath);
            cutterUpButton.setIcon(pix);
        }
        else{
            pix.load(cutterUpButton.imgpath);
            cutterUpButton.setIcon(pix);
        }
    }
}
void playscene::setlabel(){
    //金币
    QPixmap image;
    image.load(":/res/crown_coin.png");
    image = image.scaled(90, 90);
    coin.setPixmap(image);
    coin.setGeometry(width()-90, 0, 90, 90);
    coin.setParent(this);
    coin.show();
    coinlabel.setFont(font);
    coinlabel.setPalette(palette);
    coinlabel.setAlignment(Qt::AlignCenter);
    coinlabel.setText("0");
    coinlabel.setGeometry(width()-90, 70, 90, 90);
    coinlabel.setParent(this);
    coinlabel.show();
    //交付物品
    image.load(":/res/iron_mine.png");
    image = image.scaled(90, 90);
    good1.setPixmap(image);
    good1.setGeometry(width()-90, 180, 90, 90);
    good1.setParent(this);
    good1.show();
    good1label.setFont(font);
    good1label.setPalette(palette);
    good1label.setAlignment(Qt::AlignCenter);
    good1label.setText("0");
    good1label.setGeometry(width()-90, 270, 90, 90);
    good1label.setParent(this);
    good1label.show();

    image.load(":/res/copper_mine.png");
    image = image.scaled(90, 90);
    good2.setPixmap(image);
    good2.setGeometry(width()-90, 360, 90, 90);
    good2.setParent(this);
    good2.show();
    good2label.setFont(font);
    good2label.setPalette(palette);
    good2label.setAlignment(Qt::AlignCenter);
    good2label.setText("0");
    good2label.setGeometry(width()-90, 450, 90, 90);
    good2label.setParent(this);
    good2label.show();

    image.load(":/res/half_copper_mine.png");
    image = image.scaled(90, 90);
    good3.setPixmap(image);
    good3.setGeometry(width()-90, 540, 90, 90);
    good3.setParent(this);
    good3.show();
    good3label.setFont(font);
    good3label.setPalette(palette);
    good3label.setAlignment(Qt::AlignCenter);
    good3label.setText("0");
    good3label.setGeometry(width()-90, 630, 90, 90);
    good3label.setParent(this);
    good3label.show();
    //交付中心
    int gridSize = map->gridSize;
    if(scenes::mapUp == false)
        Tgood1label.setFont(font);
    else
        Tgood1label.setFont(font2);
    Tgood1label.setPalette(palette);
    Tgood1label.setAlignment(Qt::AlignCenter);
    Tgood1label.setText(QString::number(map->handedGoods[3])+"/"+QString::number(task[3]));
    Tgood1label.setGeometry(gridSize * (map->centPos.x - map->startPos[map->level].x) + gridSize*3/2, gridSize * (map->centPos.y - map->startPos[map->level].y + 2) - gridSize/2, gridSize * 2, gridSize);
    Tgood1label.setParent(this);
    Tgood1label.show();
    if(scenes::mapUp == false)
        Tgood2label.setFont(font);
    else
        Tgood2label.setFont(font2);
    Tgood2label.setPalette(palette);
    Tgood2label.setAlignment(Qt::AlignCenter);
    Tgood2label.setText(QString::number(map->handedGoods[3])+"/"+QString::number(task[3]));
    Tgood2label.setGeometry(gridSize * (map->centPos.x - map->startPos[map->level].x) + gridSize*3/2, gridSize * (map->centPos.y - map->startPos[map->level].y + 1) - gridSize/2, gridSize * 2, gridSize);
    Tgood2label.setParent(this);
    Tgood2label.show();
    if(scenes::mapUp == false)
        Tgood3label.setFont(font);
    else
        Tgood3label.setFont(font2);
    Tgood3label.setPalette(palette);
    Tgood3label.setAlignment(Qt::AlignCenter);
    Tgood3label.setText(QString::number(map->handedGoods[3])+"/"+QString::number(task[3]));
    Tgood3label.setGeometry(gridSize * (map->centPos.x - map->startPos[map->level].x) + gridSize*3/2, gridSize * (map->centPos.y - map->startPos[map->level].y + 3) - gridSize/2, gridSize * 2, gridSize);
    Tgood3label.setParent(this);
    Tgood3label.show();
}
//构建各类设备
void playscene::drillcreat(){
    createvent = 1;
    tmpdir = 0;
    imageLabel->show();
    imageLabel->setPixmap(QPixmap(":/res/miner.png"));
    imageLabel->setScaledContents(true);
    QPoint cursorPos = QCursor::pos();
    imageLabel->setGeometry(cursorPos.x() - map->gridSize / 2, cursorPos.y() - map->gridSize / 2, map->gridSize, map->gridSize);
}
void playscene::beltcreat(){
    createvent = 2;
    tmpdir = 0;
    imageLabel->show();
    imageLabel->setPixmap(QPixmap(":/res/belt_top0.png"));
    imageLabel->setScaledContents(true);
    QPoint cursorPos = QCursor::pos();
    imageLabel->setGeometry(cursorPos.x() - map->gridSize / 2, cursorPos.y() - map->gridSize / 2, map->gridSize, map->gridSize);
}
void playscene::cuttercreat(){
    createvent = 3;
    tmpdir = 0;
    imageLabel->show();
    imageLabel->setPixmap(QPixmap(":/res/cutter.png"));
    imageLabel->setScaledContents(true);
    QPoint cursorPos = QCursor::pos();
    imageLabel->setGeometry(cursorPos.x(), cursorPos.y() - map->gridSize / 2, 2 * map->gridSize, map->gridSize);
}
void playscene::bincreat(){
    createvent = 4;
    tmpdir = 0;
    imageLabel->show();
    imageLabel->setPixmap(QPixmap(":/res/trash.png"));
    imageLabel->setScaledContents(true);
    QPoint cursorPos = QCursor::pos();
    imageLabel->setGeometry(cursorPos.x() - map->gridSize / 2, cursorPos.y() - map->gridSize / 2, map->gridSize, map->gridSize);
}
void playscene::rotatercreat(){
    createvent = 5;
    tmpdir = 0;
    imageLabel->show();
    imageLabel->setPixmap(QPixmap(":/res/rotater0.png"));
    imageLabel->setScaledContents(true);
    QPoint cursorPos = QCursor::pos();
    imageLabel->setGeometry(cursorPos.x() - map->gridSize / 2, cursorPos.y() - map->gridSize / 2, map->gridSize, map->gridSize);
}
//音乐播放
void playscene::musicEvent(){
    if (mediaPlayer.state() == QMediaPlayer::PlayingState) {
        mediaPlayer.pause();
        QPixmap pix;
        pix.load(musicButton.clkImgpath);
        musicButton.setIcon(pix);
        musicButton.setIconSize(QSize(90,90));
    } else {
        mediaPlayer.play();
        QPixmap pix;
        pix.load(musicButton.imgpath);
        musicButton.setIcon(pix);
        musicButton.setIconSize(QSize(90,90));
    }
}

