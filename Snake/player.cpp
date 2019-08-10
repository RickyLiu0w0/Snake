#include "player.h"

player::player(int id  , const QString & name , const QString & password , double score , int rank)
    :ID(id), name(name), password(password), score(score),rank(rank)
{
}


//访问和设置玩家ID
void player::setId(int id)
{
    this->ID = id;
}

int player::getId() const
{
    return ID;
}

//访问和设置玩家姓名
void player::setName(QString name)
{
    this->name = name; //浅拷贝，但当（ this->name）发生改变，触发深拷贝
}
QString player::getName()  const
{
    return name;
}

//访问和设置玩家密码
void player::setPassword(QString password)
{
    for (int var = 0; var < password.length(); var++)
    {
        this->password += base64_encryption(QString::number(password.at(var).toLatin1(),2));
    }
}
QString player::getPassword() const
{
    return password;
}

//访问和设置玩家分数
void player::setScore(double score)
{
    this->score = score;
}
double player::getScore() const
{
    return score;
}

//访问和设置玩家排名
void player::setRank(int rank)
{
    this->rank = rank;
}
int player::getRank() const
{
    return rank;
}

QString player::base64_encryption(const QString input)
{
    int i = 0;
    int k = 0;
    const int n = input.length();
    QString subs;
    QString output;
    QString value = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    while (n-i >= 24)
    {
        for (k = 0; k < 4; k++)
        {
            subs = input.mid(i + k * 6 , 6);
            int sum = 0;
            int j = 0;

            for (auto & x  : subs)
            {
                sum += (x.toLatin1() -  '0') * pow(2, 5 - j); //toAscii 已被移除
                j++;
            }
            output += value.at(sum);
        }
        i += 24;
    }

   if (i != n)
   {
       int charlen;

       if ((n - i) % 6 == 0)
           charlen = (n - i ) /6 ;
       else
           charlen = (n - i ) /6 + 1;
       for (k = 0; k < charlen; k++)
       {
           subs = input.mid( i + k * 6, i + (k + 1) * 6 - 1)   ;

           int sum = 0;
           int j = 0;

           for (auto & x :subs)
           {
               sum += (x.toLatin1() -  '0') * pow(2, 5 - j); //toAscii 已被移除
               j++;
           }

           output += value.at(sum);
       }

       if ((n - i) % 16 == 0)
           output += "=";
       else
           output += "==";
        }
   return output;
}
