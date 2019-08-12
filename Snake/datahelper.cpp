#include "datahelper.h"

bool dataHelper::singalInstant = false;

dataHelper::dataHelper()
{
    if (singalInstant)
    {
        qDebug("dataHelper 不能被创建两次");
        exit(1);
    }
    else
    {
        singalInstant = true;
        count = 0;
    }
}

void dataHelper::creatFile(fstream &file)
{
    file.seekp(0);
    file.peek();
   // qDebug("location == %s", qPrintable(  QString::number(file.tellp(),10)));
   // qDebug("file.eof() == %d", file.eof());
    if (file.eof()) //判断是否为首次创建的文件
    {
         file.clear();
        qDebug("文件首次创建");
       //  qDebug("sizeof == %d", sizeof (count));
        file.write(reinterpret_cast<const char * >(&count), sizeof (count));
        //file.flush();
        //qDebug("写完之后location == %s", qPrintable(  QString::number(file.tellp(),10)));
    }
    else
    {
       file.clear();
       qDebug("文件非首次创建");
       file.seekg(0);
       file.read(reinterpret_cast< char * >(&count), sizeof (count));
    }
}

int dataHelper::saveData(fstream& file, player& pla)
{
    file.seekg(0);
    file.read(reinterpret_cast< char * >(&count), sizeof (count));
    //qDebug("count = %d", count);
    count ++;
    pla.setId(count);
    file.seekp((count - 1) *sizeof (player) + sizeof (count)); //含有隐式类型转换
    file.write(reinterpret_cast<const char *>(&pla), sizeof (player));
    file.seekp(0);
    file.write(reinterpret_cast<const char * >(&count), sizeof (count));
    return count;
}

player dataHelper::getDatabyId(fstream& file, int id)
{
    player pla;
    //qDebug("(id - 1) *sizeof (player) + sizeof (count) == %d", (id - 1) *sizeof (player) + sizeof (count));
    file.seekg((id - 1) *sizeof (player) + sizeof (count));
     //qDebug("location == %s", qPrintable(  QString::number(file.tellp(),10)));
    file.read(reinterpret_cast< char * >(&pla), sizeof (player));
     //qDebug("读完之后location == %s", qPrintable(  QString::number(file.tellp(),10)));
     qDebug("ID = %d",  pla.getId());
     qDebug("name = %s", qPrintable( pla.getName()));

    return pla;
}

QList<player> dataHelper::getAllPlayer(fstream& file)
{
    file.seekg(sizeof (count));
    QList<player> list;
    player pla ;

    /**方法一
    while (file.peek() != EOF) //解决读两次
    {
        file.read(reinterpret_cast<char * >( & pla), sizeof(player));
        list.append(pla);
    }
    file.clear();
    */

    /**方法二*/
    for (int i = 0; i < count; i++)
    {
        file.read(reinterpret_cast<char * >( & pla), sizeof(player));
        list.append(pla);
    }
    return list;
}

/**
 * @brief dataHelper::isExist
 * @param file
 * @param name
 * @return bool
 * 通过名字查看是否新人
 */
bool dataHelper::isExist(fstream& file, QString name)
{
    QList<player> list;
    player pla;
    list = getAllPlayer(file);
    for (int i = 0; i < list.size(); i++)
    {
        pla = list.at(i);
        if (QString::compare(name, pla.getName()) == 0)
            return  true;
    }
    return false;
}

 void dataHelper::updata(fstream& file , player& pla)
 {
      file.seekg((pla.getId() - 1) *sizeof (player) + sizeof (count));
      file.write(reinterpret_cast<const char *>(&pla), sizeof (player));
 }

  void dataHelper::caculateRank(fstream& file)
  {
      QList<player> list;
      int rank = 1;
      list = getAllPlayer(file);
      player pal;
      for (int i = 0; i < list.size(); i++)
      {
          rank = 1;
           for (int j = 0; j < list.size(); j++)
               if (list.at(i).getScore() < list.at(j).getScore())
                   rank++;
           pal = list.at(i);//要把引用给过去
           pal.setRank(rank);//不能用at
           updata(file,pal);
      }
  }

void dataHelper::clearAll(fstream &file)
{
    file.seekg(0);
    count = 0;
     file.write(reinterpret_cast<const char * >(&count), sizeof (count));
     truncate("data.dat",sizeof(count));
     file.flush();
}

player dataHelper::getDatabyName(fstream &file, QString name)
{
    QList<player> list;
    player pla;
    list = getAllPlayer(file);
    for (int i = 0; i < list.size(); i++)
    {
        pla = list.at(i);
        if (QString::compare(name, pla.getName()) == 0)
            return pla;
    }
    return *(new player);
}

string dataHelper::getCurrentPath()
{
    QString curPath = QCoreApplication::applicationDirPath();//获取系统当前目录
    curPath += "/data.dat";
    qDebug("path : %s", qPrintable(curPath));
    string path = curPath.toStdString();
    return path;
}
