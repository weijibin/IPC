#ifndef MYUDPSOCKET_H
#define MYUDPSOCKET_H

#include<QString>
#include <QObject>
#include <thread>
#include <iostream>

#include <WinSock2.h>
#include <stdio.h>
#define	BUF_SIZE	10240

class HHIPC;
class MyUdpSocket : public QObject
{
    Q_OBJECT
public:
    MyUdpSocket(int port,HHIPC * ipc);
    virtual ~MyUdpSocket();
    void sendMsg(QString str);
    void closed();
public slots:
    void receiveMsg();
private:
    SOCKADDR_IN addrClient;
    SOCKADDR_IN addrSrv;
    SOCKET socketSrv;
private:
    char strRecv[BUF_SIZE] = {0};
private:
    HHIPC * m_ipc = nullptr;
    bool m_isRunning = true;
};

#endif // MYUDPSOCKET_H
