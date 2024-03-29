#include "wallunit.h"

WallUnit::WallUnit(int xPos, int yPos) :Unit (xPos,yPos)
{
}

/**
 * @brief WallUnit::show
 * @param p
 * @param UNIT_SIZE
 * @overload
 * 函数重载
 */
void WallUnit::show(QPainter & p, int UNIT_SIZE) const
{
    p.drawRect(get_xPos() * UNIT_SIZE,  get_yPos() * UNIT_SIZE, UNIT_SIZE, UNIT_SIZE);
    p.fillRect(get_xPos() * UNIT_SIZE, get_yPos() * UNIT_SIZE, UNIT_SIZE, UNIT_SIZE, QColor(253, 246, 227));
}
