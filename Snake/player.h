#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <cmath>

class player
{
    public:
        //构造函数
        player(const QString & name =  "", const QString & password =  "");

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
        void setScore(int scoreValue);
        int getScore() const;

        //访问和设置玩家排名
        void setRank(int rankValue);
        int getRank() const;

        //判断玩家密码是否正确，比较的是参数password的正确性
        bool isCorrect(QString password);

    private:
        int ID;
        char name[12];
        char password[14];//10*4\3
        int score;
        int rank;

        QString base64_encryption(const QString input); //base64 加密函数
};

#endif // PLAYER_H
