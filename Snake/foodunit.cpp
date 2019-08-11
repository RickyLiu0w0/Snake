#include "foodunit.h"

FoodUnit::FoodUnit(int xPos , int yPos , int weight) : Unit (xPos, yPos)
{
        setScore(weight);
}

void FoodUnit::setScore(int weight)
{
    if (weight >3)
        weight = 3;
    score = weight;
}

int FoodUnit::getScore() const
{
    return score;
}

void FoodUnit::show(QPixmap pixmap, int UNIT_SIZE) const
{
    QPainter painter(&pixmap);
    painter.drawRect(get_xPos() * UNIT_SIZE,  get_yPos() * UNIT_SIZE, UNIT_SIZE, UNIT_SIZE);
    switch (getScore())
    {
        //1级食物，洋红色
        case 1:  painter.fillRect(get_xPos() * UNIT_SIZE, get_yPos() * UNIT_SIZE, UNIT_SIZE, UNIT_SIZE, QColor(236, 89, 247)); break;

       //2级食物，紫红色
        case 2:  painter.fillRect(get_xPos() * UNIT_SIZE, get_yPos() * UNIT_SIZE, UNIT_SIZE, UNIT_SIZE, QColor(136, 47, 142)); break;

        //3级食物，红色
        case 3: painter.fillRect(get_xPos() * UNIT_SIZE, get_yPos() * UNIT_SIZE, UNIT_SIZE, UNIT_SIZE, QColor(237, 64, 37)); break;

        default: break;
    }
}
