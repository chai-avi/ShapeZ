#include "installations.h"
void Installations:: uninstall(){
    InstallMap[pos] = nullptr;
}

driller::driller(position p, int direction):Installations (p)
{
    size_x = 1;
    size_y = 1;
    type = 1;
    dir = direction % 4;
    validOut.append({p.x+Directions[dir].x, p.y+Directions[dir].y});
    InstallMap[pos] = this;
    imgpath = ":/res/miner0.png";
}
void driller::work(){

}
//driller::~driller(){
//    uninstall();
//}

belt::belt(position p, int direction):Installations (p)
{
    size_x = 1;
    size_y = 1;
    type = 2;
    dir = direction % 4;
    validOut.append({p.x+Directions[dir].x, p.y+Directions[dir].y});
    for(int i = (dir+1)%4; i != dir; i=(i+1)%4)
        validIn.append({p.x+Directions[i].x, p.y+Directions[i].y});
    InstallMap[pos] = this;
    imgpath = ":/res/belt_top.png";
}

cuter::cuter(position p, int direction):Installations (p)
{
    size_x = 1;
    size_y = 2;
    type = 3;
    dir = direction % 4;
    validIn.append({p.x+Directions[(dir+2)%4].x, p.y+Directions[(dir+2)%4].y});
    validOut.append({p.x+Directions[dir].x, p.y+Directions[dir].y});
    validOut.append({p.x+Directions[dir].x+Directions[(dir+1)%4].x, p.y+Directions[dir].y+Directions[(dir+1)%4].y});
    InstallMap[pos] = this;
    InstallMap[{pos.x+Directions[(dir+1)%4].x, pos.y+Directions[(dir+1)%4].y}] = this;
    imgpath = ":/res/ccutter.png";
}

trash::trash(position p):Installations (p)
{
    dir = 0;
    size_x = 1;
    size_y = 1;
    type = 4;
    for(int i = 0; i < 4; i++)
        validIn.append({p.x+Directions[i].x, p.y+Directions[i].y});
    InstallMap[pos] = this;
    imgpath = ":/res/ttrash.png";
}
QMap<position, Installations*> Installations:: InstallMap;

