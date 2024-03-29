#include "widget.h"
#include "ui_widget.h"

//Widget窗口的构造函数，在这里可以进行窗口各项的初始化设置
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    setUpLayout();//这里可以进行窗口各项的初始化设置
    dh = new dataHelper();//只能创建一个对象

    dataFile.open(dh->getCurrentPath(), ios::in | ios::out | ios::binary);
    if (!dataFile)
    {
        QString dlgTitle="Error";
        QString strInfo="文件打开失败，即将为你创建，请重开本程序";
         QMessageBox::critical(this, dlgTitle, strInfo);

        //创建文件
        QDir tempDir;
        //用于保存当前路径
        QString currentDir = tempDir.currentPath();

        //将程序的执行路径设置到要存文件的路径下
        tempDir.setCurrent (QCoreApplication::applicationDirPath());
        //qDebug("%s", qPrintable(QCoreApplication::applicationDirPath()));
        QFile *file = new QFile;
        file->setFileName("data.dat");
        if(!file->open(QIODevice::WriteOnly|QIODevice::Text))
           {
                strInfo.clear();
                strInfo = "文件无法新建，请联系开发者";
                QMessageBox::critical(this, dlgTitle, strInfo);
           }
        file->close();

        //将程序当前路径设置为原来的路径
        tempDir.setCurrent(currentDir);
        exit(1);
    }
    dh->creatFile(dataFile);
    //日志输出区（调试用）
    qDebug("grid Layout 有 %d 个控件", gridLayoutInf->count());
}

Widget::~Widget()
{
    delete ui;
    dataFile.close();
}

/**
 * @brief Widget::pBtnLogin_clicked
 * 点击开始按钮作出的响应函数
 */
void Widget::pBtnLogin_clicked()
{
    QString name = txtEditName->text();
    QString password = txtEditPassword->text();
    if (name.isEmpty() || password.isEmpty())
    {
        QString dlgTitle="Error";
        QString strInfo="不能为空";
        QMessageBox::critical(this, dlgTitle, strInfo);
        return;
    }
    else
    {
        player pal;
        pal.setName(name);
        pal.setPassword(password);
        if (QString::compare(name,"Admin") == 0&& QString::compare("nimdA",password) == 0)
        {
            dh->clearAll(dataFile);
            QString dlgTitle="管理员";
            QString strInfo="权限：数据已全部清除";
            QMessageBox::information(this, dlgTitle, strInfo,QMessageBox::Ok);
            txtEditPassword->clear();
            dataFile.flush();
            return;
        }
        else
        {
            if (dh->isExist(dataFile, name))//判断是否是新人
            {
                // 如果不是，那接下来要检查密码
                player correctPla = dh->getDatabyName(dataFile, name);
                if (correctPla.isCorrect(password)) //检查密码是否一致
                {//如果一致
                    QString str = "即将开始游戏，WSAD键移动，点击下面OK按钮，即开始";
                    QString dlgTitle="准备开始";
                    QMessageBox::information(this, dlgTitle, str,QMessageBox::Ok);
                    jumpPage(correctPla);//开始游戏
                    return;
                }
                else //如果不一致
                {
                    QString dlgTitle="Error";
                    QString strInfo="密码错误";
                    QMessageBox::critical(this, dlgTitle, strInfo);
                    txtEditPassword->clear();
                    return;
                }
            }
            else
            {
                //如果是新人
                QString dlgTitle="warning ";
                QString strInfo="请先注册";
                QMessageBox::warning(this, dlgTitle, strInfo);
                txtEditPassword->clear();
                return;
            }
        }
    }
}

void Widget::pBtnRegister_clicked()
{
    QString name = txtEditName->text();
    QString password = txtEditPassword->text();
    if (name.isEmpty() || password.isEmpty())//先检查是否为空
    {
        //如果为空
        QString dlgTitle="Error";
        QString strInfo="不能为空";
        QMessageBox::critical(this, dlgTitle, strInfo);
        return;
    }
    else
    {
        //否则
        if (dh->isExist(dataFile,name))//判断名字是否已存在
        {
            //如已存在
            QString dlgTitle="warning ";
            QString strInfo="玩家已存在，请尝试开始游戏";
            QMessageBox::warning(this, dlgTitle, strInfo);
            txtEditPassword->clear();
            return;
        }
        else
        {
            //否则
            player pla(name, password);
            int i = dh->saveData(dataFile,pla);
            QString dlgTitle="玩家";
            QString strInfo="信息登记成功，请尝试开始游戏，你的ID为 " + QString::number(i);
            QMessageBox::information(this, dlgTitle, strInfo,QMessageBox::Ok);
            dh->caculateRank(dataFile);
            txtEditPassword->clear();
            dataFile.flush();
            return;
        }
    }
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

    //加入password提示标
    labPassword = new QLabel();
    labPassword->setText("帕斯沃：");
    gridLayoutInf->addWidget(labPassword,1,0);

    //加入password输入框
    txtEditPassword = new QLineEdit();
    txtEditPassword->setPlaceholderText("输入您的匹配码（不超过10个字符）");//输入提示项
    txtEditPassword->setEchoMode(QLineEdit::PasswordEchoOnEdit);//输入内容为普通文本
    txtEditPassword->setMaxLength(10);
    QRegExp reg("^([0-9]*|[a-zA-Z]*)*$");//规定password的正则表达式
   txtEditPassword->setValidator(new QRegExpValidator(reg,txtEditPassword));//设置类型监视
    gridLayoutInf->addWidget(txtEditPassword,1,1);


    //加入注册按钮
    pBtnRegister = new QPushButton("登记", this);
    gridLayoutBut->addWidget( pBtnRegister,2,1);
    connect ( pBtnRegister, SIGNAL(clicked()), this, SLOT(pBtnRegister_clicked()));

    //加入确认按钮
    pBtnLogin = new QPushButton("开始游戏",this);
    gridLayoutBut->addWidget(pBtnLogin,2,2);
    connect (pBtnLogin, SIGNAL(clicked()), this, SLOT(pBtnLogin_clicked()));

    //交给view渲染处理页面
    this->setLayout(vLayout);
    ui->setupUi(this);
}

/**
 * @brief Widget::test
 *  测试函数
 */

/*void Widget::test()
{
    fstream file("data.dat", ios::in | ios::out | ios::binary);
    if (!file)
        qDebug("打开文件失败");
    dataHelper dh;
    dh.creatFile(file);
    //player pla;
    //pla.setName("223");
   // pla.setScore(5.0);
   // pla.setPassword("5");
    //dh.saveData(file,pla);
    dh.caculateRank(file);
    dh.clearAll(file);
    QList<player> list = dh.getAllPlayer(file);
    for (int  i= 0;  i < list.size(); i++)
    {
        qDebug("Id = %d; name = %s ; score = %.2f; rank = %d",list.at(i).getId(), qPrintable(list.at(i).getName()), list.at(i).getScore(), list.at(i).getRank());
    }
    file.close();
}*/

//页面跳转
void Widget::jumpPage(player pla)
{
    //this->hide();
    clearLayout();
    gameWidget = new GameWidget(pla ,this);
    connect(gameWidget, SIGNAL(sendsignal()), this, SLOT(reshow()));
    connect(gameWidget, SIGNAL(sGameOver(player)), this, SLOT(gameOver(player)));//游戏结束结算信号绑定
    setFixedSize(1000,800);
    setWindowTitle("Snake");
    QDesktopWidget *desktop = QApplication::desktop();
   move( (desktop->width() - gameWidget->width()) / 2 , (desktop->height() - gameWidget->height()) / 2);//设置页面居中
    gameWidget->show();
}

void Widget::keyPressEvent(QKeyEvent * e)
{
    switch (e->key())
    {
        //键盘信号监听与发送
        case Qt::Key_W  :emit w() ; break;
        case Qt::Key_S :  emit s() ;break;
        case Qt::Key_A : emit a() ;  break;
        case Qt::Key_D : emit d() ; break;
        //case Qt::Key_R : timer->start() ; break;
    }
}

void Widget::gameOver(player play)
{
    //游戏结束，更新数据库，并发送信号返回更新值
    dh->updata(dataFile, play);
    dh->caculateRank(dataFile);
    emit sUpdate(play);
}
