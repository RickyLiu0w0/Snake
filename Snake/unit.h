#ifndef UNIT_H
#define UNIT_H
#include <QPixmap>
#include <QPainter>

//虚基类
class Unit
{
    public:
        Unit(int xPos = 0, int yPos = 0);
        virtual ~Unit();//不能成为内联函数

        void moveEast();
        void moveWest();
        void moveNorth();
        void moveSouth();

        void set_xPos(int xPos);
        void set_yPos(int yPos);

        int get_xPos() const;
        int get_yPos() const;

        virtual void show(QPainter &p, int UNIT_SIZE) const = 0;//虚函数

    private:
        int x;
        int y;
};

#endif // UNIT_H
