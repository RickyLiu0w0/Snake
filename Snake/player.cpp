#include "player.h"

player::player(int id  , const QString & name , const QString & password , double score , int rank)
    :ID(id), score(score),rank(rank)
{
    setName(name);
    setPassword(password);
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
    char* ptr;
    QByteArray by;
    by = name.toLatin1();
    ptr = by.data();
    memcpy(this->name,ptr,12);//这一句，必须加，不然不只是把指针指向了值，并没有赋值
    qDebug("ID: %s", this->name);
}
QString player::getName()  const
{
    return name;
}

//访问和设置玩家密码
void player::setPassword(QString password)
{
    QString temp = "";
    for (int var = 0; var < password.length(); var++)
    {
        temp += base64_encryption(QString::number(password.at(var).toLatin1(),2));
    }
    char* ptr;
    QByteArray by;
    by = temp.toLatin1();
    ptr = by.data();
    memcpy(this->password,ptr,28);
    qDebug("password: %s", qPrintable(this->password) );
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
