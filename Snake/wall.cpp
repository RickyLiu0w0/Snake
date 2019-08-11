#include "wall.h"

Wall::Wall(int height, int width)
{
    WallUnit* temp;
    //开始建造围墙
    for (int i = 0; i < height; i++)
    {
        if ( height - 1== i || 0 == i) //第一层和最后一层全部填满wall单元
            for (int j = 0; j < width; j++)
            {
                temp = new WallUnit(i,j);
                wall.append(temp);        //这点加入wall的列表中
            }
        else
        {
            temp = new WallUnit(i,0);
            wall.append(temp);
            temp = new WallUnit(i, width - 1);
            wall.append(temp);
        }
    }
}

int Wall::getSize()
{
    return wall.size();
}

WallUnit Wall::getWallUnit(int i)
{
    return *(wall.at(i));
}
