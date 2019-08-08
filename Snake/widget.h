#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

#include "gamewidget.h"

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
        void pBtnTest_clicked();
        void reshow();

    private:
        Ui::Widget *ui;

        //游戏界面成员
        GameWidget * gameWidget;
        QGridLayout * gridLayout;

        //当前页面各控件成员
        QLabel * labLogin ; //输入框标签
        QLineEdit * txtEdit; //名字输入框
        QPushButton * pBtnTest;//登入按钮

        void clearLayout();
        void setUpLayout();
};

#endif // WIDGET_H
