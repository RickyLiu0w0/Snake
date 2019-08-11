#ifndef SNAKEUNIT_H
#define SNAKEUNIT_H
#include "unit.h"

class SnakeUnit: public Unit
{
    public:
        SnakeUnit(int xPos = 0, int yPos = 0);
        void show(QPixmap pixmap, int UNIT_SIZE) const ;

        void setToHead();
        void setToBody();

        bool isBody();
        bool isHead();

    private:
        bool flagHead;
        bool flagBody;
};

#endif // SNAKEUNIT_H
