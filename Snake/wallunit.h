#ifndef WALLUNIT_H
#define WALLUNIT_H
#include "unit.h"
//继承
class WallUnit :public Unit
{
    public:
        WallUnit(int xPos = 0, int yPos = 0);
        void show(QPainter & p, int UNIT_SIZE) const ;
};

#endif // WALLUNIT_H
