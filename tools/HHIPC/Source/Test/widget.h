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

    QString m_msg;

private slots:
    void on_pushButton_clicked();

    void sltRecvMsg(const QString &str);
    void sltRecvMsg1(const QString &str);

private:
    Ui::Widget *ui;
    QUdpSocket *udpSocket;
    QUdpSocket *udpSocket1;

    HHIPC *m_ipc1 = nullptr;
    HHIPC *m_ipc2 = nullptr;
    HHIPC *m_ipc3 = nullptr;
    HHIPC *m_ipc4 = nullptr;
    HHIPC *m_ipc5 = nullptr;
    HHIPC *m_ipc6 = nullptr;
    HHIPC *m_ipc7 = nullptr;
    HHIPC *m_ipc8 = nullptr;
    HHIPC *m_ipc9 = nullptr;
    HHIPC *m_ipc10 = nullptr;
};

#endif // WIDGET_H
