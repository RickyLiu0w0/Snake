#ifndef WALL_H
#define WALL_H

#include <QList>

#include "wallunit.h"

class Wall
{
    public:
        Wall(int height, int width);
        int getSize();
        WallUnit getWallUnit(int i);
    private:
        QList<WallUnit * > wall ;
};

#endif // WALL_H
