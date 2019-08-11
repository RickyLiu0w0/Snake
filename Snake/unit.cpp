#include "unit.h"

Unit::Unit(int xPos, int yPos)
{
    set_xPos(xPos);
    set_yPos(yPos);
}

Unit::~Unit() { }

void Unit::moveEast()
{
    x++;
}

void Unit::moveSouth()
{
    y++;
}

void Unit::moveWest()
{
    x--;
}

void Unit::moveNorth()
{
    y--;
}


void Unit::set_xPos(int xPos)
{
    x = xPos;
}
void Unit::set_yPos(int yPos)
{
    y = yPos;
}

int Unit::get_xPos() const
{
    return x;
}
int Unit::get_yPos() const
{
    return y;
}

/*
void Unit::show(QPixmap pixmap, int UNIT_SIZE)
{
    QPainter painter(&pixmap);
    painter.drawRect(x * UNIT_SIZE, y * UNIT_SIZE, UNIT_SIZE, UNIT_SIZE);
    if (isSnakeHead())
    {
        painter.fillRect(x * UNIT_SIZE, y * UNIT_SIZE, UNIT_SIZE, UNIT_SIZE, Qt::blue);
    }
    else if (isSnakeBody())
    {
        painter.fillRect(x * UNIT_SIZE, y * UNIT_SIZE, UNIT_SIZE, UNIT_SIZE, Qt::black);
    }else if (isWall())
    {
        painter.fillRect(x * UNIT_SIZE, y * UNIT_SIZE, UNIT_SIZE, UNIT_SIZE, QColor(253, 246, 227));
    }
}
*/
