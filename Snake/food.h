#ifndef FOOD_H
#define FOOD_H

#include <ctime>
#include "foodunit.h"

class Food
{
    public:
        Food(int hight, int width, int weight);
        FoodUnit * getFoodUnit() const;

    private:
        FoodUnit * foo;
        FoodUnit fo;
};

#endif // FOOD_H
