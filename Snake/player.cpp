#include "player.h"

player::player(const QString & name , const QString & password )
{
    setId(0);
    setName(name);
     setPassword(password);
    setScore(0);
    setRank(1);
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
    QString tempResult = "";

    tempResult = base64_encryption(password);
    //由QString转换为Char *

    //在调用QByteArray.data()之前，必须要先显示储存这个bytearray。像这样const char *ch = str.toLatin1().data();会使程序崩溃，因为QByteArray没有被储存，调用data()前是不存在的，必须先显式调用一次toLatin1()，再调用data()。
    char* ptr;
    QByteArray by;
    by = tempResult.toLatin1();
    ptr = by.data();
    memcpy(this->password,ptr,14); //!!!!!!!!!!!!!!!

    qDebug("password: %s", qPrintable(this->password) );
}
QString player::getPassword() const
{
    return password;
}

//访问和设置玩家分数
void player::setScore(double scoreValue)
{
    this->score = scoreValue;
}
double player::getScore() const
{
    return score;
}

//访问和设置玩家排名
void player::setRank(int rankValue)
{
    this->rank = rankValue;
}
int player::getRank() const
{
    return rank;
}

QString player::base64_encryption(const QString input)
{
    QString passBin = "";
    QString binResult = "";
    for (int var = 0; var < input.length(); var++)
    {
       passBin.clear();
       passBin = QString::number(input.at(var).toLatin1(),2);
       qDebug("Binary Before: %s", qPrintable(passBin) );
       //为了补全8位二进制
       if (passBin.length() < 8)
       {
           QString passBinHelp =passBin;
            passBin.clear();
           for (int i = 0; i < 8 - passBinHelp.length(); i++)
           {
               passBin += "0";
           }
           passBin += passBinHelp;
       }

       //将每一个8位二进制连接起来
       binResult += passBin;
    }
     qDebug("Binary After: %s", qPrintable(binResult) );
    int i = 0;
    int k = 0;
    const int n =binResult .length();
    QString subs;
    QString output;
    QString value = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    while (n-i >= 24)
    {
        for (k = 0; k < 4; k++)
        {
            subs = binResult.mid(i + k * 6 , 6);
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
           subs = binResult.mid( i + k * 6, i + (k + 1) * 6 - 1)   ;

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


bool player::isCorrect(QString password)
{
    qDebug("用户输入的密码是：%s", qPrintable(password));
    QString result =  base64_encryption(password);
    qDebug("原密码是：%s", qPrintable(this->password));
    return QString::compare(this->password,result) == 0;
}
