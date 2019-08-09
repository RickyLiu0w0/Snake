#include "widget.h"
#include "ui_widget.h"

//Widget窗口的构造函数，在这里可以进行窗口各项的初始化设置
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    setUpLayout();//这里可以进行窗口各项的初始化设置

    //日志输出区（调试用）
    qDebug("grid Layout 有 %d 个控件", gridLayoutInf->count());
}

Widget::~Widget()
{
    delete ui;
}

void Widget::pBtnLogin_clicked()
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
    while (vLayout->count())
    {
        QWidget * pWidget = vLayout->itemAt(0)->widget();
        if(pWidget)
        {
            pWidget->setParent(nullptr);
            vLayout->removeWidget(pWidget);
            delete pWidget;
        }
        else
        {
            QLayout * pLayout = vLayout->itemAt(0)->layout();
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
            vLayout->removeItem(vLayout->itemAt(0));
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

   vLayout = new QVBoxLayout();//创建水平布局
   gridLayoutInf = new  QGridLayout();//创建栅格布局
   gridLayoutBut = new QGridLayout();

   vLayout->addLayout(gridLayoutInf);
   vLayout->addLayout(gridLayoutBut);
    //加入名字提示标签
    labName = new QLabel();
    labName->setText("玩家姓名：");
    gridLayoutInf->addWidget(labName,0,0);

    //加入名字输入框
    txtEditName = new QLineEdit();
    txtEditName->setPlaceholderText("输入您的玩家姓名（不超过10个字符）");//输入提示项
    txtEditName->setMaxLength(10);//设置长度，不超10字符
    txtEditName->setEchoMode(QLineEdit::Normal);//输入内容为普通文本
    gridLayoutInf->addWidget(txtEditName,0,1);

    //加入password提示标签
    labPassword = new QLabel();
    labPassword->setText("帕斯沃：");
    gridLayoutInf->addWidget(labPassword,1,0);

    //加入passwo输入框
    txtEditPassword = new QLineEdit();
    txtEditPassword->setPlaceholderText("输入您的匹配码");//输入提示项
    txtEditPassword->setEchoMode(QLineEdit::PasswordEchoOnEdit);//输入内容为普通文本
    QRegExp reg("^([0-9]*|[a-zA-Z]*)*$");//规定password的正则表达式
   txtEditPassword->setValidator(new QRegExpValidator(reg,txtEditPassword));//设置类型监视
    gridLayoutInf->addWidget(txtEditPassword,1,1);

    //加入确认按钮
    pBtnLogin = new QPushButton("push",this);
    gridLayoutBut->addWidget(pBtnLogin,0,1);
    connect (pBtnLogin, SIGNAL(clicked()), this, SLOT(pBtnLogin_clicked()));

    //交给view渲染处理页面
    this->setLayout(vLayout);
    ui->setupUi(this);
}