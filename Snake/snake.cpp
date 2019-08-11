#include "snake.h"

Snake:: Snake(int hight, int length)
{
    direction = East;
    fieldLength = length;
    fileHigth = hight;
    alive = true;
    int beginX = length / 2;
    int beginY =hight / 2;
    SnakeUnit * s;
    s = new SnakeUnit(beginX, beginY);
    s->setToHead();
    snake.append(s);
    s = new SnakeUnit(beginX - 1, beginY );
    s->setToBody();
    snake.append(s);
    s = new SnakeUnit(beginX - 2, beginY);
    s->setToBody();
    snake.append(s);
}
