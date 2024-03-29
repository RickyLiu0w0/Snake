#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QRegExpValidator>
#include <QMessageBox>
#include <QKeyEvent>
#include <QDesktopWidget>
#include <QDir>
#include <QCoreApplication>

#include "gamewidget.h"
#include "datahelper.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
        Q_OBJECT

    public:
        explicit Widget(QWidget *parent = nullptr);
        ~Widget();

    private slots:
        void pBtnLogin_clicked();
        void reshow();
        void pBtnRegister_clicked();
        void gameOver(player pal);
       //void test();

    private:
        Ui::Widget *ui;

        //游戏界面成员
        GameWidget * gameWidget;
        QVBoxLayout * vLayout;// 垂直布局
        QGridLayout * gridLayoutInf;//栅格布局（放置玩家信息）
        QGridLayout * gridLayoutBut;//栅格布局（放置按钮）

        //当前页面各控件成员
        QLabel * labName ; //输入框标签
        QLineEdit * txtEditName; //名字输入框
        QLabel * labPassword; // 匹配码标签
        QLineEdit * txtEditPassword; //匹配码输入框
        QPushButton * pBtnLogin;//登入按钮
        QPushButton * pBtnRegister;//开档按钮
        dataHelper * dh;//数据处理
        fstream dataFile; //储存数据

        void clearLayout();//清除UI界面
        void setUpLayout();//生成UI界面
        void jumpPage(player pla);//跳转页面
        void keyPressEvent(QKeyEvent * e)   ;//监听键盘事件

    signals:
        //待发射的信号，按键信号和结算信号
        void w();
        void a();
        void s();
        void d();
        void sUpdate(player);

};

#endif // WIDGET_H
