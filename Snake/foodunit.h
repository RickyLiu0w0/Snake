#ifndef FOODUNIT_H
#define FOODUNIT_H

#include "unit.h"

class FoodUnit : public Unit
{
    public:
        FoodUnit(int xPos = 0, int yPos = 0 , int weight = 1);

        int getScore() const;
        void setScore(int weight) ;

        void show(QPixmap pixmap, int UNIT_SIZE) const ;

    private:
        int score;
};

#endif // FOODUNIT_H
