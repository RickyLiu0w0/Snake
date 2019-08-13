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

