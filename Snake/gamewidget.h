#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPixmap>
#include <QLabel>
#include <QLCDNumber>
#include <QPushButton>
#include <QSpacerItem>
#include <QTimer>
#include<QMessageBox>

#include "garden.h"
#include "player.h"

namespace Ui {
class GameWidget;
}

class GameWidget : public QWidget
{
        Q_OBJECT

    public:
        explicit GameWidget(player pla, QWidget *parent = nullptr);
        ~GameWidget();


    private slots:
        void pushButton_clicked();
        void  timeOut();
        void w_c();
        void s_c();
        void a_c();
        void d_c();
        void upDate(player pla);

    private:
        Ui::GameWidget *ui;

        //游戏界面成员
        QVBoxLayout * vLayout;// 垂直布局
        QHBoxLayout * hLayout; //水平布局
        QLabel * labMap;//放画布
        QWidget  * Widget;

        //控件
        QPixmap * map; //游戏画布
        QLabel * labPlayName; //展示玩家姓名
        QLCDNumber * playerScore; //展示玩家分数
        QPushButton * pBtnQuit; //退出按钮
        QSpacerItem * spa; //分割器
         QTimer * timer;

        //游戏的成员
        static Garden * garden;
        player  pla;

        static bool signalCount ;
        const int MAP_SIZE;
        const int UNIT_SIZE;
         int time;

         void paint();


    signals:
        void sendsignal();
        void sGameOver(player pal);
};

#endif // GAMEWIDGET_H
