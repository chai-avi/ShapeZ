#include "shopscene.h"

shopscene::shopscene(): mapButton(":/res/mapup0.JPG", ":/res/mapup1.JPG"),mineButton(":/res/mineup0.JPG", ":/res/mineup1.JPG"),moneyButton(":/res/coinup0.JPG", ":/res/coinup1.JPG"),exitButton(":/res/exit.png", "")
{
    //storeLabel, mapLabel, mineLabel, moneyLabel, coin, coinlabel
    QPixmap image;
    image.load(":/res/store.jpg");
    image = image.scaled(width()/2,height()/4);
    storeLabel.setPixmap(image);
    storeLabel.setGeometry(width()/4, 100, width()/2,height()/4);
    storeLabel.setParent(this);
    storeLabel.show();
    image.load(":/res/map.png");
    image = image.scaled(400,400);
    mapLabel.setPixmap(image);
    mapLabel.setGeometry(width()/8+80, height()/3, 500, 500);
    mapLabel.setParent(this);
    mapLabel.show();
    image.load(":/res/mineral.png");
    image = image.scaled(400,400);
    mineLabel.setPixmap(image);
    mineLabel.setGeometry(width()*3/8+80, height()/3, 500, 500);
    mineLabel.setParent(this);
    mineLabel.show();
    image.load(":/res/coins.png");
    image = image.scaled(400,400);
    moneyLabel.setPixmap(image);
    moneyLabel.setGeometry(width()*5/8+80, height()/3, 500, 500);
    moneyLabel.setParent(this);
    moneyLabel.show();
    image.load(":/res/crown_coin.png");
    image = image.scaled(90, 90);
    coin.setPixmap(image);
    coin.setGeometry(width()-90, 0, 90, 90);
    coin.setParent(this);
    coin.show();
    coinlabel.setFont(font);
    coinlabel.setPalette(palette);
    coinlabel.setAlignment(Qt::AlignCenter);
    coinlabel.setText(QString::number(scenes::money));
    coinlabel.setGeometry(width()-90, 70, 90, 90);
    coinlabel.setParent(this);
    coinlabel.show();
    //mapButton, mineButton, moneyButton, exitButton
    mapButton.setParent(this);
    mapButton.setFixedSize(width()/4,height()/5);
    mapButton.setIconSize(QSize(width()/4,height()/5));
    mapButton.move(width()/8, height()*2/3);
    mineButton.setParent(this);
    mineButton.setFixedSize(width()/4,height()/5);
    mineButton.setIconSize(QSize(width()/4,height()/5));
    mineButton.move(width()*3/8, height()*2/3);
    moneyButton.setParent(this);
    moneyButton.setFixedSize(width()/4,height()/5);
    moneyButton.setIconSize(QSize(width()/4,height()/5));
    moneyButton.move(width()*5/8, height()*2/3);
    exitButton.move(width()- 200, height()-150);
    exitButton.setIconSize(QSize(100,100));
    exitButton.setParent(this);
    connect(&mapButton, &mypushbutton::clicked, this, [=](){
        if(scenes::mapUp == false && scenes::money >= 100){
            scenes::mapUp = true;
            QPixmap pix;
            pix.load(mapButton.clkImgpath);
            mapButton.setIcon(pix);
            money -= 100;
            coinlabel.setText(QString::number(scenes::money));
        }
    });
    connect(&mineButton, &mypushbutton::clicked, this, [=](){
        if(scenes::mineUp == false && scenes::money >= 100){
            scenes::mineUp = true;
            QPixmap pix;
            pix.load(mineButton.clkImgpath);
            mineButton.setIcon(pix);
            money -= 100;
            coinlabel.setText(QString::number(scenes::money));
        }
    });
    connect(&moneyButton, &mypushbutton::clicked, this, [=](){
        if(scenes::moneyUp == false && scenes::money >= 100){
            scenes::moneyUp = true;
            QPixmap pix;
            pix.load(moneyButton.clkImgpath);
            moneyButton.setIcon(pix);
            money -= 100;
            coinlabel.setText(QString::number(scenes::money));
        }
    });
}
