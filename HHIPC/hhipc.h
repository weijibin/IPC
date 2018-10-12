#ifndef HHIPC_H
#define HHIPC_H

#include <QObject>
#include "hhipc_global.h"

class QUdpSocket;

typedef void (*ReceiveInfo)(QString str);
class HHIPCSHARED_EXPORT HHIPC : public QObject
{
    Q_OBJECT
public:

    HHIPC();
    HHIPC(ReceiveInfo * recv);

    void sentInfo(QString str);

signals:
    void sigRecvInfo(const QString &info);

private:
    QUdpSocket * m_udpSocket = nullptr;
    ReceiveInfo *m_recvF;

};

#endif // HHIPC_H
