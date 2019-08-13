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

/**
 * @brief FoodUnit::show
 * @param p
 * @param UNIT_SIZE
 * @overload
 * 绘制食物的函数，实现Unit类的虚函数
 */
void FoodUnit::show(QPainter & p, int UNIT_SIZE) const
{
    p.drawRect(get_xPos() * UNIT_SIZE,  get_yPos() * UNIT_SIZE, UNIT_SIZE, UNIT_SIZE);//(x坐标，y坐标，长，宽)
    switch (getScore())
    {
        //1级食物，洋红色
        case 1:  p.fillRect(get_xPos() * UNIT_SIZE, get_yPos() * UNIT_SIZE, UNIT_SIZE, UNIT_SIZE, QColor(236, 89, 247)); break;

       //2级食物，紫红色
        case 2:  p.fillRect(get_xPos() * UNIT_SIZE, get_yPos() * UNIT_SIZE, UNIT_SIZE, UNIT_SIZE, QColor(136, 47, 142)); break;

        //3级食物，红色
        case 3: p.fillRect(get_xPos() * UNIT_SIZE, get_yPos() * UNIT_SIZE, UNIT_SIZE, UNIT_SIZE, QColor(237, 64, 37)); break;

        default: break;
    }
}
