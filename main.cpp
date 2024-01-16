#include "shapez.h"
#include <QApplication>
#include <QResource>
#include <QSettings>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ShapeZ w;
    QApplication::quit();

    return a.exec();
}
