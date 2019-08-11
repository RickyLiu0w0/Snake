#ifndef WALLUNIT_H
#define WALLUNIT_H
#include "unit.h"

class WallUnit :public Unit
{
    public:
        WallUnit(int xPos = 0, int yPos = 0);
        void show(QPixmap pixmap, int UNIT_SIZE) const ;
};

#endif // WALLUNIT_H
