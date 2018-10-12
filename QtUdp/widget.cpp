#include "widget.h"
#include "ui_widget.h"

#include "hhipc.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    m_ipc1 = new HHIPC;
    m_ipc2 = new HHIPC;

    connect(m_ipc1, &HHIPC::sigRecvInfo, [=,this](QString info)
    {
            ui->textEdit->append("udpReceive111111::"+info);
    });

    connect(m_ipc2, &HHIPC::sigRecvInfo, [=,this](QString info)
    {
        ui->textEdit->append("udpReceive22222::"+info);
    });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    qDebug()<<"Client send msg";
    m_ipc1->sentInfo("Client send msg");
}
