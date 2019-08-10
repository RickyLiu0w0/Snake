#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <cmath>

class player
{
    public:
        //构造函数
        player(int id = 0 , const QString & name =  "", const QString & password =  "", double score = 0.0, int rank = 0);

        //访问和设置玩家ID
        void setId(int id);
        int getId() const;

        //访问和设置玩家姓名
        void setName(QString name);
        QString getName()  const ;

        //访问和设置玩家密码
        void setPassword(QString passwprd);
        QString getPassword() const;

        //访问和设置玩家分数
        void setScore(double score);
        double getScore() const;

        //访问和设置玩家排名
        void setRank(int rank);
        int getRank() const;

    private:
        int ID;
        char name[12];
        char password[29];//21*4\3
        double score;
        int rank;

        QString base64_encryption(const QString input); //base64 加密函数
};

#endif // PLAYER_H
