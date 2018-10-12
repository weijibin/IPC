#include "hhipc.h"
#include <QUdpSocket>
#include <QByteArray>
#include <QDebug>

const quint16 PORT = 23333;

HHIPC::HHIPC()
{
    m_udpSocket = new QUdpSocket;
    m_udpSocket->bind(QHostAddress("127.0.0.1"),PORT,QAbstractSocket::ShareAddress | QAbstractSocket::ReuseAddressHint);
    m_udpSocket->joinMulticastGroup(QHostAddress::Broadcast);
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

void HHIPC::sentInfo(QString str)
{
    QByteArray ba = str.toLocal8Bit();
    m_udpSocket->writeDatagram(ba.data(),ba.size(),QHostAddress::Broadcast,PORT);
}
