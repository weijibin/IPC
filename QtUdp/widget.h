#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QUdpSocket>
#include <QDebug>

namespace Ui {
class Widget;
}

class HHIPC;
class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
    QUdpSocket *udpSocket;
    QUdpSocket *udpSocket1;

    HHIPC *m_ipc1 = nullptr;
    HHIPC *m_ipc2 = nullptr;
};

#endif // WIDGET_H
