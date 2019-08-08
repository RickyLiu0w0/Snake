#include "widget.h"
#include "ui_widget.h"

//Widget窗口的构造函数，在这里可以进行窗口各项的初始化设置
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{

    setUpLayout();//这里可以进行窗口各项的初始化设置

    //日志输出区（调试用）
    qDebug("grid Layout 有 %d 个控件", gridLayout->count());

}

Widget::~Widget()
{
    delete ui;
}

void Widget::pBtnTest_clicked()
{
    //this->hide();
    clearLayout();
     gameWidget = new GameWidget(this);
    connect(gameWidget, SIGNAL(sendsignal()), this, SLOT(reshow()));
    setFixedSize(600,600);
    setWindowTitle("Snake");
    gameWidget->show();
}

void Widget::reshow()
{
    //setWindowTitle("开始");
    //setFixedSize(300,400);
    setUpLayout();
    this->show();
}

void Widget::clearLayout()
{
    while (gridLayout->count())
    {
        QWidget * pWidget = gridLayout->itemAt(0)->widget();
        if(pWidget)
        {
            pWidget->setParent(nullptr);
            gridLayout->removeWidget(pWidget);
            delete pWidget;
        }
        else
        {
            QLayout * pLayout = gridLayout->itemAt(0)->layout();
            if(pLayout)
            {
                while (pLayout->count())
                {
                    QWidget * pTemptWidget = pLayout->itemAt(0)->widget();
                    if( pTemptWidget)
                    {
                         pTemptWidget->setParent(nullptr);
                        pLayout->removeWidget( pTemptWidget);
                        delete  pTemptWidget;
                    }
                    else
                    {
                        pLayout->removeItem(pLayout->itemAt(0));
                    }
                }
            }
            gridLayout->removeItem(gridLayout->itemAt(0));
        }
    }
    if (this->layout())
        delete this->layout();
}

void Widget::setUpLayout()
{
    setWindowTitle("开始");//开始界面标题
    setFixedSize(400,200);//固定开始窗口大小

    //禁止窗口最大化
    Qt::WindowFlags flags = nullptr;
    flags |= Qt::WindowMinimizeButtonHint;
    setWindowFlags(flags);
    //结束

   gridLayout = new QGridLayout();//创建栅格布局

    //加入编辑框标签
    labLogin = new QLabel();
    labLogin->setText("玩家姓名：");
    gridLayout->addWidget(labLogin,0,0);

    //加入确认按钮
    pBtnTest = new QPushButton("push",this);
    gridLayout->addWidget(pBtnTest,0,1);
    connect (pBtnTest, SIGNAL(clicked()), this, SLOT(pBtnTest_clicked()));

    //交给view渲染处理页面
    this->setLayout(gridLayout);
    ui->setupUi(this);
}
