#include "hhipc.h"
#include <QUdpSocket>
#include <QByteArray>
#include <QDebug>

const quint16 PORT = 23333;

HHIPC::HHIPC()
{
    m_udpSocket = new QUdpSocket;

    QHostAddress addr;
    addr.setAddress(QHostAddress::AnyIPv4);
    m_broadCastAddr.setAddress("224.0.2.17");

//    addr.setAddress(QHostAddress::LocalHost);
//    m_broadCastAddr.setAddress(QHostAddress::Broadcast);

    m_udpSocket->bind(addr,PORT,QAbstractSocket::ShareAddress | QAbstractSocket::ReuseAddressHint);
    m_udpSocket->joinMulticastGroup(m_broadCastAddr);

    m_udpSocket->setSocketOption(QAbstractSocket::ReceiveBufferSizeSocketOption,1024*1024*8);

    connect(m_udpSocket, &QUdpSocket::readyRead, [=,this]()
    {
        QByteArray ba;
        while(m_udpSocket->hasPendingDatagrams())
        {
            ba.resize(m_udpSocket->pendingDatagramSize());
            m_udpSocket->readDatagram(ba.data(), ba.size());
            emit sigRecvInfo(ba);
        }
    });
}


HHIPC::HHIPC( ReceiveInfo *recv) : HHIPC()
{
    m_recvF = recv;
}

HHIPC::~HHIPC()
{
    m_udpSocket->leaveMulticastGroup(m_broadCastAddr);
    m_udpSocket->deleteLater();
}

void HHIPC::sentInfo(QString str)
{
    QByteArray ba = str.toLocal8Bit();
    m_udpSocket->writeDatagram(ba.data(),ba.size(),m_broadCastAddr,PORT);
}
