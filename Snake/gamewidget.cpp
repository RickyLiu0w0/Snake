#include "gamewidget.h"
#include "ui_gamewidget.h"

GameWidget::GameWidget(player pla, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWidget), pla(pla),UNIT_SIZE(800)
{
    qDebug("玩家：%s", qPrintable(pla.getName()));
    qDebug("分数：%d", pla.getScore());
    qDebug("排名：%d", pla.getRank());
    hLayout = new QHBoxLayout(this); //创建水平布局
    vLayout = new QVBoxLayout(this); //创建垂直布局

    //加入画布
    map = new QPixmap(UNIT_SIZE,UNIT_SIZE); //创建画布
    labMap = new QLabel();//创建承接画布的容器
    hLayout->addWidget(labMap);//将容器放在左边
    labMap->setPixmap(*map); //把画布放在容器中

    //将显示信息的容器放在右边
    hLayout->addLayout(vLayout);

    //加入显示玩家姓名
    QString str = pla.getName() + " 玩家\n你好\n你之前的排名是\n第 " + QString::number( pla.getRank()) + " 名";
    labPlayName = new QLabel(str ,this);

    QFont font;//设置字体大小
    font.setPointSize(20);
    labPlayName->setFont(font);

    labPlayName->setMinimumSize(labPlayName->width(), labPlayName->height()); //设置label的大小
    labPlayName->setMaximumSize(3 * labPlayName->width(), 4 * labPlayName->height());
    labPlayName->setScaledContents(true);//与文字适应

    vLayout->addWidget(labPlayName);

    //加入LCD计分器
    playerScore = new QLCDNumber();
    playerScore->setDigitCount(2);
    vLayout->addWidget(playerScore);
    playerScore->setSegmentStyle(QLCDNumber::Flat);

    //分割器
    spa = new QSpacerItem(0,60,QSizePolicy::Expanding, QSizePolicy::Minimum);
    vLayout->addItem(spa);

    //返回按钮
    pBtnQuit = new QPushButton("返回", this);
    pBtnQuit->setStyleSheet("QPushButton{font-size:20px}");
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

