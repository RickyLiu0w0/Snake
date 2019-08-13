#include "datahelper.h"

bool dataHelper::singalInstant = false;//控制对象只能创建一次

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

/**
 * @brief dataHelper::creatFile
 * @param file
 * 创建数据库文件
 */
void dataHelper::creatFile(fstream &file)
{
    file.seekp(0);
    file.peek();//需要读取一下下一个字符，才能知道到末尾没有
    if (file.eof()) //判断是否为首次创建的文件
    {
         file.clear();//重设goodbit位
        qDebug("文件首次创建");
       //  qDebug("sizeof == %d", sizeof (count));
        file.write(reinterpret_cast<const char * >(&count), sizeof (count));//初始化文件，以二进制的写入文件
        //file.flush();
    }
    else
    {
       file.clear();//重设goodbit位，其实这里可以不用
       qDebug("文件非首次创建");
       file.seekg(0);
       file.read(reinterpret_cast< char * >(&count), sizeof (count));//读取文件里面的记录数目
    }
}

/**
 * @brief dataHelper::saveData
 * @param file
 * @param pla
 * @return 新建玩家的ID号
 *
 */
int dataHelper::saveData(fstream& file, player& pla)
{
    file.seekg(0);//文件定位指针
    file.read(reinterpret_cast< char * >(&count), sizeof (count));
    //qDebug("count = %d", count);
    count ++;
    pla.setId(count);
    file.seekp((count - 1) *sizeof (player) + sizeof (count)); //含有隐式类型转换
    file.write(reinterpret_cast<const char *>(&pla), sizeof (player));//写入玩家数据
    file.seekp(0);
    file.write(reinterpret_cast<const char * >(&count), sizeof (count));//更新文件记录数
    return count;
}

/**
 * @brief dataHelper::getDatabyId
 * @param file
 * @param id
 * @return 寻找到的玩家
 * 根据id寻找玩家信息
 */
player dataHelper::getDatabyId(fstream& file, int id)
{
    player pla;
    file.seekg((id - 1) *sizeof (player) + sizeof (count)); //  根据id号搜索文件
    file.read(reinterpret_cast< char * >(&pla), sizeof (player));//读取文件信息
     //qDebug("ID = %d",  pla.getId());
     //qDebug("name = %s", qPrintable( pla.getName()));
    return pla;
}

/**
 * @brief dataHelper::getAllPlayer
 * @param file
 * @return 玩家的列表
 * 返回整个数据库记录
 */
QList<player> dataHelper::getAllPlayer(fstream& file)
{
    file.seekg(sizeof (count));
    QList<player> list;
    player pla ;

    //两种方法来遍历，我个人选择了第二种的
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
     //更新对应玩家的信息
      file.seekg((pla.getId() - 1) *sizeof (player) + sizeof (count));
      file.write(reinterpret_cast<const char *>(&pla), sizeof (player));
 }

 /**
   * @brief dataHelper::caculateRank
   * @param file
   * 根据文件中的玩家分数计算排名
   */
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
    //清库
    file.seekg(0);
    count = 0;
     file.write(reinterpret_cast<const char * >(&count), sizeof (count));//计数重设0
     truncate("data.dat",sizeof(count));//把文件截断，留下计数
     file.flush();
}

/**
 * @brief dataHelper::getDatabyName
 * @param file
 * @param name
 * @return 玩家
 */
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
    return *(new player); //如果没有，就新建一个玩家返回去
}

string dataHelper::getCurrentPath()
{//为了创建和打开数据文件而设的
    QString curPath = QCoreApplication::applicationDirPath();//获取系统当前目录
    curPath += "/data.dat";
    qDebug("path : %s", qPrintable(curPath));
    string path = curPath.toStdString();
    return path;
}
