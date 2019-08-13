#include "garden.h"

Garden::Garden(int hight, int length)
{
       sna  = new Snake(hight, length);
       wal = new Wall(hight, length);
       foo = new Food(hight,length,1);
       this->Hight = hight;
       this->Length = length;
       score = 0;
}

int Garden::getHight()
{
    return Hight;
}

int Garden::getLength()
{
    return Length;
}

int Garden::getScore() const
{
    return score;
}

int Garden::getWallSize() const
{
    return wal->getSize();
}

int Garden::getSnackSize() const
{
    return sna->getSnakeSize();
}

SnakeUnit * Garden::getUnitFromSanck(int i)
{
    return sna->getSnackUnit(i);
}

WallUnit * Garden::getUnitFromWall(int i)
{
    return wal->getWallUnit(i);
}

FoodUnit * Garden::getUnitFromFood()
{
    return  foo->getFoodUnit();
}

void Garden::w_onClick()
{
    switch (sna->direction)
    {
        case Snake::North : break;//本来向上，所以不做任何操作
        case Snake::South : break; //原路径返回，必死无疑，设置放呆功能
        case Snake::West : sna->moveToNorth(); break;
        case Snake:: East : sna->moveToNorth();break;
    }
}

void Garden::s_onClick()
{
    switch (sna->direction)
    {
        case Snake::North : break;
        case Snake::South : break;
        case Snake::West : sna->moveToSouth(); break;
        case Snake::East : sna->moveToSouth(); break;
    }
}

void Garden::a_onClick()
{
    switch (sna->direction)
    {
        case Snake::North : sna->moveToWest();break;
        case Snake::South : sna->moveToWest();break;
        case Snake::West : break;
        case Snake:: East : break;
    }
}

void Garden::d_onClick()
{
    switch (sna->direction)
    {
        case Snake::North : sna->moveToEast(); break;
        case Snake::South : sna->moveToEast(); break;
        case Snake::West : break;
        case Snake:: East : break;
    }
}

//移动蛇，判断是否存活，或吃了食物
 bool Garden::isContinue()
 {
     bool result;
     sna->move();
     result = sna->isAlive();

     //采用吃了食物，才会生成新食物的机制
     if (sna->isEatFood(foo))
     {
         int weight;
         score += foo->getFoodUnit()->getScore();
         qDebug("Score = %d", score);

         if (score < 5 )
             weight = 1;
         else if (score < 15)
         {
             weight = 2;
         }
         else {
             weight = 3;
         }
         foo = new Food(Hight , Length  , weight);
     }
     return result;
 }
