#ifndef GARDEN_H
#define GARDEN_H

#include "snake.h"
#include "wall.h"
#include "food.h"
#include "player.h"


class Garden
{
    public:
        Garden(int hight, int length);

        int getHight();
        int getLength();

        int getScore() const;

        int getWallSize() const;
        int getSnackSize() const;

        SnakeUnit * getUnitFromSanck(int i) ;
        WallUnit * getUnitFromWall(int i);
        FoodUnit * getUnitFromFood();

        void w_onClick();
        void s_onClick();
        void a_onClick();
        void d_onClick();

        bool isContinue();

    private:
        int Hight;
        int Length;
        int score;
        Snake * sna;
        Food * foo;
        Wall * wal;
};

#endif // GARDEN_H
