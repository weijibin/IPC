#ifndef HHIPC_H
#define HHIPC_H

#include <QObject>
#include "hhipc_global.h"

class MyUdpSocket;
class QThread;
class HHIPCSHARED_EXPORT HHIPC : public QObject
{
    Q_OBJECT
public:
    /**
    Description:	根据端口号 创建IPC对象
    @param	[in]	端口号port (推荐范围：23333~25555)
    @exception      none
    */
    HHIPC(int port = 23333);
    virtual ~HHIPC();
    void sentInfo(const QString &str);
signals:
    void sigRecvInfo(const QString &info);
private:
    MyUdpSocket * mysocket = nullptr;
private:
    int m_port = 23333;
    QThread *m_thread = nullptr;
};

#endif // HHIPC_H
