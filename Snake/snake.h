#ifndef SNAKE_H
#define SNAKE_H

#include "snakeunit.h"
#include "food.h"

//蛇单元的一个整合
class Snake
{
    public:
        Snake(int hight, int length);
        int getSnakeSize();
        SnakeUnit * getSnackUnit (int i);

        void move();
        void moveToEast();
        void moveToSouth();
        void moveToWest();
        void moveToNorth();

        bool isEatFood(Food *foo);
        bool isHitWall();
        bool isHitSnake();
        bool isAlive();

        enum directionEnum  //蛇的方向
        {
            East, South, West, North
        } direction;

    private:
        int fieldLength;
        int fileHigth;
        bool alive;
        QList<SnakeUnit * > snake;

};

#endif // SNACK_H
