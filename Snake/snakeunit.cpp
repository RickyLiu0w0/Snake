#include "snakeunit.h"
SnakeUnit::SnakeUnit(int xPos, int yPos) :Unit (xPos,yPos)
{
    flagBody = false;
    flagHead = false;
}

void SnakeUnit::show(QPainter & p, int UNIT_SIZE) const
{
    p.drawRect(get_xPos() * UNIT_SIZE,  get_yPos() * UNIT_SIZE, UNIT_SIZE, UNIT_SIZE);
    if (flagBody)
        p.fillRect(get_xPos() * UNIT_SIZE, get_yPos() * UNIT_SIZE, UNIT_SIZE, UNIT_SIZE, Qt::black);
    else if (flagHead)
    {
        p.fillRect(get_xPos() * UNIT_SIZE, get_yPos() * UNIT_SIZE, UNIT_SIZE, UNIT_SIZE, Qt::blue);
    }
}

void SnakeUnit::setToBody()
{
    flagBody = true;
}

void SnakeUnit::setToHead()
{
    flagHead = true;
}

bool SnakeUnit::isBody()
{
    return flagBody;
}

bool SnakeUnit::isHead()
{
    return flagHead;
}
