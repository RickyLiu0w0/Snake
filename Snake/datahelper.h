#ifndef DATAHELPER_H
#define DATAHELPER_H

#include <QList>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <QCoreApplication>
#include "player.h"
using namespace std;
class dataHelper
{
    public:
        dataHelper();
        void creatFile(fstream& file);
        int saveData(fstream& file, player& pla);
        player getDatabyId(fstream& file, int id);
        QList<player> getAllPlayer(fstream& file);
        bool isExist(fstream& file, QString name);
        void updata(fstream& file ,player& pla);
        void caculateRank(fstream& file);
        void clearAll(fstream& file);
        player getDatabyName(fstream& file, QString name);
        string getCurrentPath();

    private:
        int count;
        static bool singalInstant;
        QString currentPath;
};

#endif // DATAHELPER_H
