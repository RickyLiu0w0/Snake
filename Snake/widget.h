#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QRegExpValidator>

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
        void test();

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

        void clearLayout();//清除UI界面
        void setUpLayout();//生成UI界面
};

#endif // WIDGET_H
