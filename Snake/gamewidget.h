#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>

namespace Ui {
class GameWidget;
}

class GameWidget : public QWidget
{
        Q_OBJECT

    public:
        explicit GameWidget(QWidget *parent = nullptr);
        ~GameWidget();

    private slots:
        void on_pushButton_clicked();


    private:
        Ui::GameWidget *ui;

    signals:
        void sendsignal();
};

#endif // GAMEWIDGET_H
