#include "hhipc.h"
#include <QUdpSocket>
#include <QByteArray>
#include <QDebug>
#include <QTime>
#include <QtConcurrent>
#include <QThread>

#include "myudpsocket.h"

HHIPC::HHIPC(int port) : m_port(port)
{
    mysocket = new MyUdpSocket(m_port,this);

    m_thread = new QThread;
    mysocket->moveToThread(m_thread);
    connect(m_thread,&QThread::started,mysocket,&MyUdpSocket::receiveMsg);
    m_thread->start();
}

HHIPC::~HHIPC()
{
//    qDebug()<<"~HHIPC() start";
    mysocket->closed();

    m_thread->quit();
    m_thread->wait();
    delete m_thread;
    delete mysocket;

//    qDebug()<<"~HHIPC() end";
}

void HHIPC::sentInfo(const QString &str)
{
    mysocket->sendMsg(str);
}
