#include "gamewidget.h"
#include "ui_gamewidget.h"

bool GameWidget::signalCount = true;

GameWidget::GameWidget(player pla, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWidget), pla(pla),MAP_SIZE(20), UNIT_SIZE(40), time(100)
{
    qDebug("玩家：%s", qPrintable(pla.getName()));
    qDebug("分数：%d", pla.getScore());
    qDebug("排名：%d", pla.getRank());
    hLayout = new QHBoxLayout(this); //创建水平布局
    vLayout = new QVBoxLayout(this); //创建垂直布局

    //加入画布
    map = new QPixmap(800,800); //创建画布
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
    pBtnQuit->setCursor(Qt::PointingHandCursor);
    setFocusPolicy(Qt::ClickFocus);
    connect ( pBtnQuit, SIGNAL(clicked()), this, SLOT(pushButton_clicked()));
    vLayout->addWidget(pBtnQuit);


    this->setLayout(hLayout);
    ui->setupUi(this);

    //创建“有蛇”的花园
    garden = new Garden(MAP_SIZE,MAP_SIZE);

    //设置计时器
    timer = new QTimer;
    connect( timer, SIGNAL(timeout()) ,this, SLOT(timeOut()));
    paint();
    timer->setInterval(time);
    timer->start() ;

    Widget = parent;
    if (GameWidget::signalCount)
    {
        connect(Widget, SIGNAL(w()), this, SLOT(w_c()));
        connect(Widget, SIGNAL(a()), this, SLOT(a_c()));
        connect(Widget, SIGNAL(s()), this, SLOT(s_c()));
        connect(Widget, SIGNAL(d()), this, SLOT(d_c()));
        connect(Widget, SIGNAL(sUpdate(player)), this, SLOT(upDate(player)));
        signalCount = false;
    }

}

GameWidget::~GameWidget()
{
    delete ui;
}

void GameWidget::pushButton_clicked()
{
    emit sendsignal();
    timer->stop();
    this->close();
}

void GameWidget::w_c()
{
    garden->w_onClick();
    qDebug("w");
}

void GameWidget::a_c()
{
    garden->a_onClick();
    qDebug("a");
}

void GameWidget::s_c()
{
    garden->s_onClick();
    qDebug("s");
}

void GameWidget::d_c()
{
    garden->d_onClick();
    qDebug("d");
}

void GameWidget::timeOut()
{
    if (!garden->isContinue())
    {
        timer->stop();
        pla.setScore(garden->getScore() + pla.getScore());
        qDebug("时间停止！");
        emit sGameOver(pla);
    }
    else
    {
    playerScore->display(garden->getScore());
    labMap->setUpdatesEnabled(true);
    labMap->update();
    map->fill(QColor(228, 228, 228));
    paint();
    }
}


void GameWidget::paint()
{
    Unit * unit;
    QPainter p(map);

    for (int i = 0 ; i < garden->getWallSize(); i ++)
    {
        unit = garden->getUnitFromWall(i);
        unit->show(p, UNIT_SIZE);
    }
    for (int i = 0; i < garden->getSnackSize() ; i++)
    {
        unit = garden->getUnitFromSanck(i);
        unit->show(p, UNIT_SIZE);
    }
    unit = garden->getUnitFromFood();
    unit->show(p, UNIT_SIZE);
    labMap->setPixmap(*map); //把画布放在容器中
}

void GameWidget::upDate(player pla)
{

    QString str = pla.getName() + " 玩家\n" +
                  "分数：" + QString::number( pla.getScore()) + "\n第 " +
                   QString::number(pla.getRank()) + " 名";
    QString dlgTitle="结果";
    QMessageBox::information(this, dlgTitle, str,QMessageBox::Ok);
}
