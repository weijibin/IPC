#include "hhipc.h"
#include <QUdpSocket>
#include <QByteArray>
#include <QDebug>
#include <QTime>
#include <QtConcurrent>

#include "myudpsocket.h"

HHIPC::HHIPC(int port) : m_port(port)
{
    mysocket = new MyUdpSocket(m_port,this);
    QtConcurrent::run(mysocket,&MyUdpSocket::receiveMsg);
}

HHIPC::~HHIPC()
{
    delete mysocket;
}

void HHIPC::sentInfo(const QString &str)
{
    mysocket->sendMsg(str);
}
