#include "food.h"

Food::Food(int hight, int width, int weight)
{
    srand(static_cast<unsigned int>(time(nullptr)));

    //要取得[a,b)的随机整数，使用(rand() % (b-a))+ a;
    foo = new FoodUnit((rand()% (hight - 2 - 2)) + 2, (rand()% (width - 2 - 2)) + 2 , weight);
}

FoodUnit * Food::getFoodUnit() const
{
    return  foo;
}
