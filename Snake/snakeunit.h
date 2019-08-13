#ifndef SNAKEUNIT_H
#define SNAKEUNIT_H
#include "unit.h"

//继承
class SnakeUnit: public Unit
{
    public:
        SnakeUnit(int xPos = 0, int yPos = 0);
        void show(QPainter & p, int UNIT_SIZE) const ;

        void setToHead();
        void setToBody();

        bool isBody();
        bool isHead();

    private:
        bool flagHead;
        bool flagBody;
};

#endif // SNAKEUNIT_H
