#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPixmap>
#include <QLabel>
#include <QLCDNumber>
#include <QPushButton>

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


    private:
        Ui::GameWidget *ui;

        //游戏界面成员
        QVBoxLayout * vLayout;// 垂直布局
        QHBoxLayout * hLayout; //水平布局
        QLabel * labMap;//放画布

        //控件
        QPixmap * map; //游戏画布
        QLabel * labPlayName; //展示玩家姓名
        QLCDNumber * playerScore; //展示玩家分数
        QPushButton * pBtnQuit; //退出按钮

        //游戏的成员
        //Garden * garden;
        player  pla;
        //Unit * unit;
        const int UNIT_SIZE;


    signals:
        void sendsignal();
};

#endif // GAMEWIDGET_H
