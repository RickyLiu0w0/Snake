#ifndef DATAHELPER_H
#define DATAHELPER_H

#include <QList>
#include <iostream>
#include <fstream>
#include "player.h"
using namespace std;
class dataHelper
{
    public:
        dataHelper();
        ~dataHelper();
        void creatFile(fstream& file);
        int saveData(fstream& file, player& pla);
        player getDatabyId(fstream& file, int id);
        QList<player> getAllPlayer(fstream& file);
        bool isExist(fstream& file, QString name);
        void updata(fstream& file ,player& pla);

    private:
        int count;
        static bool singalInstant;
};

#endif // DATAHELPER_H
