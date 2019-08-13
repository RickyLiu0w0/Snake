#include "snake.h"

Snake:: Snake(int hight, int length)
{
    direction = East;
    fieldLength = length;
    fileHigth = hight;
    alive = true;
    //初始化中间，三节
    int beginX = length / 2;
    int beginY =hight / 2;
    SnakeUnit * s;
    s = new SnakeUnit(beginX, beginY);
    s->setToHead();
    snake.append(s);
    s = new SnakeUnit(beginX - 1, beginY );
    s->setToBody();
    snake.append(s);
    s = new SnakeUnit(beginX - 2, beginY);
    s->setToBody();
    snake.append(s);
}

int Snake::getSnakeSize()
{
    return snake.size();
}

SnakeUnit * Snake::getSnackUnit(int i)
{
    return snake.at(i);
}

void Snake::move() //这里可以解释以下用了QList的好处，因为频繁获取插入元素，所以链表开销比较小，不用整体移动
{
    SnakeUnit * temp;
    for (int i = snake.size() -1 ; i > 0 ; i--)
    {
        //用后一个方块代替前一个，达到前进的目的
        temp = snake.takeAt(i); //takeAt会从链表中删除，所以要加回去
        temp->set_xPos(snake.at(i - 1)->get_xPos());
        temp->set_yPos(snake.at(i - 1)->get_yPos());
        snake.insert(i, temp);
    }

    switch (direction) {
        case East :
            temp = snake.takeAt(0);
            temp->moveEast();
            snake.insert(0, temp);
            break;

        case South :
            temp = snake.takeAt(0);
            temp->moveSouth();
            snake.insert(0,temp);
            break;

        case West :
            temp = snake.takeAt(0);
            temp->moveWest();
            snake.insert(0, temp);
            break;

        case North :
            temp = snake.takeAt(0);
            temp->moveNorth();
            snake.insert(0, temp);
    }
}

//这些好像没啥必要，因为direction 是public 的，直接改就是了，这里是为了代码美观
void Snake::moveToEast()
{
    direction = East;
}

void Snake::moveToSouth()
{
    direction = South;
}

void Snake::moveToWest()
{
    direction = West;
}

void Snake::moveToNorth()
{
    direction = North;
}
//-------------------------------------------------

bool Snake::isEatFood(Food *foo)
{
    bool result ;
    result = (snake.at(0)->get_xPos() == foo->getFoodUnit()->get_xPos())
            && (snake.at(0)->get_yPos() == foo->getFoodUnit()->get_yPos());
    if (result)
    {
        SnakeUnit * body = snake.takeAt(0);
        body->setToBody();
        snake.insert(0, body);//食物变成身体
        SnakeUnit* head = new SnakeUnit(foo->getFoodUnit()->get_xPos(), foo->getFoodUnit()->get_yPos());
        head->setToHead();//头部向前移动
        switch (direction)
        {
            case  East : head->moveEast(); break;
            case  South : head->moveSouth(); break;
            case West: head->moveWest() ; break;
            case North :head->moveNorth(); break;
        }
        snake.insert(0, head);
    }
    return result;
}

bool Snake::isHitWall()//判断是否撞墙
{
    bool result ;
   // qDebug("snake.at(0)->get_xPos()  == %d", snake.at(0)->get_xPos() );
    //qDebug("snake.at(0)->get_yPos()  == %d", snake.at(0)->get_yPos() );
    result = snake.at(0)->get_xPos() >= fileHigth - 1
             ||  snake.at(0)->get_xPos() <= 0
             ||  snake.at(0)->get_yPos() >= fieldLength - 1
             ||  snake.at(0)->get_yPos() <= 0;
    return result;
}

bool Snake::isHitSnake()//判断是否自咬
{
    bool result = false;
    for (int i = 1; i < snake.size() - 1; i ++)  //去头
    {
        result = snake.at(0)->get_xPos() == snake.at(i)->get_xPos()
               &&  snake.at(0)->get_yPos() == snake.at(i)->get_yPos();
        if (result)
            break;
    }
    return result;
}

bool Snake::isAlive()
{
    alive = !isHitWall() && !isHitSnake();
    return alive;
}
