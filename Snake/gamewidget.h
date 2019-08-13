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
        //信号槽，监听本页面按钮点击信号和Widget传来的函数执行信号
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
        QWidget  * Widget;//上一页面的指针

        //控件
        QPixmap * map; //游戏画布
        QLabel * labPlayName; //展示玩家姓名
        QLCDNumber * playerScore; //展示玩家分数
        QPushButton * pBtnQuit; //退出按钮
        QSpacerItem * spa; //分割器
         QTimer * timer;//计数器

        //游戏的成员
        static Garden * garden;
        player  pla;

        static bool signalCount ;//控制信号只建立一次连接
        const int MAP_SIZE;//图的大小
        const int UNIT_SIZE;//方块大小
         int time;//控制时间

         void paint();//绘制画布


    signals:
         //发送出去的信号
        void sendsignal();
        void sGameOver(player pal);
};

#endif // GAMEWIDGET_H
