#include "startscene.h"

startscene::startscene(): newgameButton(":/res/newgame.jpg", ""), loadButton(":/res/load.jpg", ""), storeButton(":/res/store.jpg", ""),exitButton(":/res/exit.png", "")
{
    // 新游戏 读取存档 商店
    newgameButton.setParent(this);
    newgameButton.setFixedSize(width()/4,height()/10);
    newgameButton.setIconSize(QSize(width()/3,height()/6));
    newgameButton.move(width()/8, height()*2/3);
    storeButton.setParent(this);
    storeButton.setFixedSize(width()/4,height()/10);
    storeButton.setIconSize(QSize(width()/3,height()/6));
    storeButton.move(width()*3/8, height()*2/3);
    loadButton.setParent(this);
    loadButton.setFixedSize(width()/4,height()/10);
    loadButton.setIconSize(QSize(width()/3,height()/6));
    loadButton.move(width()*5/8, height()*2/3);
    exitButton.move(width()- 90, height()-90);
    exitButton.setIconSize(QSize(70,70));
    exitButton.setParent(this);
//    connect(&newgameButton, &mypushbutton::clicked, this, &startscene::newgame);
//    connect(&storeButton, &mypushbutton::clicked, this, &startscene::store);
//    connect(&loadButton, &mypushbutton::clicked, this, &startscene::load);

    QPixmap image;
    image.load(":/res/big_logo.png");
    image = image.scaled(width()/2, height()/4-50);
    backgroundLabel.setPixmap(image);
    backgroundLabel.setGeometry(200, 100, width()/2, height()/4-50);
    backgroundLabel.setParent(this);
    backgroundLabel.show();

    image.load(":/res/play.png");
    image = image.scaled(400,400);
    newgameLabel.setPixmap(image);
    newgameLabel.setGeometry(width()/8+80, height()/3, 500, 500);
    newgameLabel.setParent(this);
    newgameLabel.show();
    image.load(":/res/shop.png");
    image = image.scaled(400,400);
    storeLabel.setPixmap(image);
    storeLabel.setGeometry(width()*3/8+80, height()/3, 500, 500);
    storeLabel.setParent(this);
    storeLabel.show();
    image.load(":/res/load.png");
    image = image.scaled(400,400);
    loadLabel.setPixmap(image);
    loadLabel.setGeometry(width()*5/8+80, height()/3, 500, 500);
    loadLabel.setParent(this);
    loadLabel.show();
}
//void startscene:: newgame(){
////    this->hide();

//}
