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
};

#endif // FOOD_H
