#include "wallunit.h"

WallUnit::WallUnit(int xPos, int yPos) :Unit (xPos,yPos)
{
}

void WallUnit::show(QPixmap pixmap, int UNIT_SIZE) const
{
    QPainter painter(&pixmap);
    painter.drawRect(get_xPos() * UNIT_SIZE,  get_yPos() * UNIT_SIZE, UNIT_SIZE, UNIT_SIZE);
    painter.fillRect(get_xPos() * UNIT_SIZE, get_yPos() * UNIT_SIZE, UNIT_SIZE, UNIT_SIZE, QColor(253, 246, 227));
}
