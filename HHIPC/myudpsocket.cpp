#include "myudpsocket.h"
#include <QTime>
#include <QDebug>
#include "hhipc.h"

MyUdpSocket::MyUdpSocket(int port, HHIPC *ipc) : m_ipc(ipc)
{
//    QTime t;
//    t.start();
    qDebug()<<"MyUdpSocket::MyUdpSocket::: start";
    WSADATA wsd;
    // 初始化套接字动态库
    if(WSAStartup(MAKEWORD(2,2), &wsd)!= 0){
        qDebug()<<QString("WSAStartup failed:%1!\n").arg(WSAGetLastError());
        return;
    }

    //广播地址
    addrClient.sin_addr.S_un.S_addr = inet_addr("255.255.255.255");
    addrClient.sin_family = AF_INET;
    addrClient.sin_port = htons(port);

    // 设置服务器地址
    //addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
    addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    addrSrv.sin_family = AF_INET;
    addrSrv.sin_port = htons(port);

    socketSrv = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);

//    qDebug()<<"================create socket :::time"<< t.elapsed();
//    t.restart();

    //设置Reuse
    int flag=1,len1=sizeof(int);
    int result = setsockopt(socketSrv, SOL_SOCKET, SO_REUSEADDR, (char*)&flag, len1);
    if( result == -1)
    {
        qDebug()<<("setsockopt REUSEADDR Error");
        exit(1);
    }

    //打开广播选项
    bool bOpt = true;
    int result1 = setsockopt(socketSrv, SOL_SOCKET, SO_BROADCAST, (char*)&bOpt, sizeof(bOpt));
    if( result1 == -1)
    {
        qDebug()<<("setsockopt BROADCAST Error");
        exit(1);
    }

//    qDebug()<<"================set socket opt :::time"<< t.elapsed();
//    t.restart();

    // 绑定套接字
    int iRet = 0;
    iRet = bind(socketSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));

//    qDebug()<<"BindResult::: "<<iRet;
//    qDebug()<<"==============bind socket :::time"<< t.elapsed();

    if(SOCKET_ERROR == iRet)
    {
        qDebug()<<QString("bind failed%d!\n").arg(WSAGetLastError());
        closesocket(socketSrv);
        WSACleanup();
    }
    qDebug()<<"MyUdpSocket::MyUdpSocket::: end";
}

MyUdpSocket::~MyUdpSocket()
{
    closesocket(socketSrv);
    WSACleanup();
}

void MyUdpSocket::sendMsg(QString str)
{
    // 向客户端发送数据
    int len = sizeof(SOCKADDR);
    QByteArray ba = str.toLocal8Bit();
    sendto(socketSrv, ba.data(), ba.size(), 0, (SOCKADDR*)&addrClient, len);
}

void MyUdpSocket::receiveMsg()
{
    //接收数据
    while(TRUE)
    {
        int iRet = 0;
        ZeroMemory(strRecv,BUF_SIZE);
        iRet = recvfrom(socketSrv,strRecv,BUF_SIZE,0,nullptr,nullptr);
        qDebug()<<"ReceiveMsg::::"<<iRet;
        if(SOCKET_ERROR == iRet){
            qDebug()<<("recvfrom failed !\n");
            closesocket(socketSrv);
            WSACleanup();
            return;
        }
        if(m_ipc)
        {
            emit m_ipc->sigRecvInfo(QString(strRecv));  //接收信号
        }
    }
}
