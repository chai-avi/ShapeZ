#ifndef STARTSCENE_H
#define STARTSCENE_H
#include"tools.h"
#include "scenes.h"

class startscene : public scenes
{
    Q_OBJECT
private:
    QLabel backgroundLabel;
public:
    explicit startscene();

signals:

public slots:
};

#endif // STARTSCENE_H
