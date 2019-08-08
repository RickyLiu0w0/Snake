#include "gamewidget.h"
#include "ui_gamewidget.h"

GameWidget::GameWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWidget)
{
    ui->setupUi(this);

}

GameWidget::~GameWidget()
{
    delete ui;
}

void GameWidget::on_pushButton_clicked()
{
    emit sendsignal();
    this->close();
}
