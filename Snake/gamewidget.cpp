#include "gamewidget.h"
#include "ui_gamewidget.h"

GameWidget::GameWidget(player pla, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWidget), pla(pla),UNIT_SIZE(800)
{
    qDebug("玩家：%s", qPrintable(pla.getName()));
    qDebug("分数：%.2f", pla.getScore());
    qDebug("排名：%d", pla.getRank());
    hLayout = new QHBoxLayout(this); //创建水平布局
    vLayout = new QVBoxLayout(this); //创建垂直布局

    //画布
    map = new QPixmap(UNIT_SIZE,UNIT_SIZE); //创建画布
    labMap = new QLabel();//创建承接画布的容器
    hLayout->addWidget(labMap);//将容器放在左边
    labMap->setPixmap(*map); //把画布放在容器中

    hLayout->addLayout(vLayout);//将显示信息的容器放在右边


    //显示玩家姓名
    QString str = pla.getName() + "玩家，你好\n你目前排名是" + QString::number( pla.getRank());
    labPlayName = new QLabel(str ,this);
    QFont font;
    font.setPointSize(20);
    labPlayName->setFont(font);
    vLayout->addWidget(labPlayName);

    //lcd
    playerScore = new QLCDNumber();
    vLayout->addWidget(playerScore);

    //quit
    pBtnQuit = new QPushButton("saa", this);
    vLayout->addWidget(pBtnQuit);
    connect ( pBtnQuit, SIGNAL(clicked()), this, SLOT(pushButton_clicked()));

    this->setLayout(hLayout);
    ui->setupUi(this);

}

GameWidget::~GameWidget()
{
    delete ui;
}

void GameWidget::pushButton_clicked()
{
    emit sendsignal();
    this->close();
}

