#ifndef DATAHELPER_H
#define DATAHELPER_H

#include <QList>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <QCoreApplication>
#include "player.h"
using namespace std;

//管理数据的一个类
class dataHelper
{
    public:
        dataHelper();
        void creatFile(fstream& file);//创建数据文件
        int saveData(fstream& file, player& pla); //保存数据
        player getDatabyId(fstream& file, int id);//通过id查找玩家信息
        QList<player> getAllPlayer(fstream& file);//获得全部玩家
        bool isExist(fstream& file, QString name);//判断玩家是否已存在
        void updata(fstream& file ,player& pla);//更新玩家数据
        void caculateRank(fstream& file);//计算数据库中的玩家排名
        void clearAll(fstream& file);//清库操作
        player getDatabyName(fstream& file, QString name);//通过名字获得玩家信息
        string getCurrentPath();//寻找数据文件的储存地址

    private:
        int count;//数据文件中的玩家数量
        static bool singalInstant;//控制单例模式
        QString currentPath;//文件路径
};

#endif // DATAHELPER_H
