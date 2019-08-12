#ifndef UNIT_H
#define UNIT_H
#include <QPixmap>
#include <QPainter>


class Unit
{
    public:
        Unit(int xPos = 0, int yPos = 0);
        virtual ~Unit();//不能成为内联函数

        //void setToFood();
        //void setToSnakeHead();
        //void setToSnakeBody();
        //void setToWall();

        void moveEast();
        void moveWest();
        void moveNorth();
        void moveSouth();

        //bool isSnakeBody();
        //bool isSnakeHead();
        //bool isWall();
        //bool isFood();

        void set_xPos(int xPos);
        void set_yPos(int yPos);

        int get_xPos() const;
        int get_yPos() const;

        virtual void show(QPainter &p, int UNIT_SIZE) const = 0;

    private:
        int x;
        int y;

        /*
        bool flagSnakeBody;
        bool flagSnakeHead;
        bool flagFood;
        bool flagWall;
        */
};

#endif // UNIT_H
