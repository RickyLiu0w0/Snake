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
    }
}

void dataHelper::creatFile(fstream &file)
{
    file.seekp(0);
    if (file.eof()) //判断是否为首次创建的文件
        file.write(reinterpret_cast<const char * >(0), sizeof (int));
}

int dataHelper::saveData(fstream& file, player& pla)
{
    file.seekg(0);
    file.read(reinterpret_cast< char * >(&count), sizeof (count));
    qDebug("count = %d", count);
    count ++;
    pla.setId(count);
    file.seekp((count - 1) *sizeof (player) + sizeof (count)); //含有隐式类型转换
    file.write(reinterpret_cast<const char *>(&pla), sizeof (player));
    return count;
}

player dataHelper::getDatabyId(fstream& file, int id)
{
    player pla;
    file.seekg((id - 1) *sizeof (player) + sizeof (count));
    file.read(reinterpret_cast< char * >(&pla), sizeof (player));
    return pla;
}

QList<player> dataHelper::getAllPlayer(fstream& file)
{
    file.seekg(sizeof (count));
    QList<player> list;
    player pla ;
    while (!file.eof())
    {
        file.read(reinterpret_cast<char * >( & pla), sizeof(player));
        list.append(pla);
    }
    return list;
}

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
