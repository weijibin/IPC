#ifndef MYUDPSOCKET_H
#define MYUDPSOCKET_H

#include<QString>
#include <thread>
#include <iostream>

#include <WinSock2.h>
#include <stdio.h>
#define	BUF_SIZE	1024

class HHIPC;
class MyUdpSocket
{
public:
    MyUdpSocket(int port,HHIPC * ipc);
    virtual ~MyUdpSocket();

    void sendMsg(QString str);
    void receiveMsg();
private:
    SOCKADDR_IN addrClient;
    SOCKADDR_IN addrSrv;
    SOCKET socketSrv;
private:
    char strRecv[BUF_SIZE] = {0};
private:
    HHIPC * m_ipc = nullptr;

};

#endif // MYUDPSOCKET_H
