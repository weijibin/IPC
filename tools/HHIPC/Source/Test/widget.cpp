#include "widget.h"
#include "ui_widget.h"

#include "hhipc.h"
#include <QTime>
#include <QThreadPool>
#include <QFile>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{

//    qDebug()<<QThreadPool::globalInstance()->maxThreadCount();
//    QThreadPool::globalInstance()->setMaxThreadCount(100);
//    qDebug()<<QThreadPool::globalInstance()->maxThreadCount();


    QTime t;
    t.start();
    qDebug()<<"Widget::start";
    ui->setupUi(this);

    m_ipc1 = new HHIPC();
//    m_ipc2 = new HHIPC();
//    m_ipc3 = new HHIPC();
//    m_ipc4 = new HHIPC();
//    m_ipc5 = new HHIPC();
//    m_ipc6 = new HHIPC();
//    m_ipc7 = new HHIPC();
//    m_ipc8 = new HHIPC();
//    m_ipc9 = new HHIPC();
//    m_ipc10 = new HHIPC();

//    connect(m_ipc1, &HHIPC::sigRecvInfo, [=,this](QString info)
//    {
//            ui->textEdit->append("udpReceive111111::"+info);
//    });

//    connect(m_ipc2, &HHIPC::sigRecvInfo, [=,this](QString info)
//    {
//        ui->textEdit->append("udpReceive22222::"+info);
//    });

    connect(m_ipc1,&HHIPC::sigRecvInfo,this,&Widget::sltRecvMsg,Qt::QueuedConnection);
//    connect(m_ipc2,&HHIPC::sigRecvInfo,this,&Widget::sltRecvMsg1,Qt::QueuedConnection);
//    connect(m_ipc3,&HHIPC::sigRecvInfo,this,&Widget::sltRecvMsg,Qt::QueuedConnection);
//    connect(m_ipc4,&HHIPC::sigRecvInfo,this,&Widget::sltRecvMsg1,Qt::QueuedConnection);
//    connect(m_ipc5,&HHIPC::sigRecvInfo,this,&Widget::sltRecvMsg,Qt::QueuedConnection);
//    connect(m_ipc6,&HHIPC::sigRecvInfo,this,&Widget::sltRecvMsg1,Qt::QueuedConnection);
//    connect(m_ipc7,&HHIPC::sigRecvInfo,this,&Widget::sltRecvMsg,Qt::QueuedConnection);
//    connect(m_ipc8,&HHIPC::sigRecvInfo,this,&Widget::sltRecvMsg1,Qt::QueuedConnection);
//    connect(m_ipc9,&HHIPC::sigRecvInfo,this,&Widget::sltRecvMsg,Qt::QueuedConnection);
//    connect(m_ipc10,&HHIPC::sigRecvInfo,this,&Widget::sltRecvMsg1,Qt::QueuedConnection);
    qDebug()<<"Widget::end  spend time======"<<t.elapsed();


    QString fileName = ":/Temp.json";
    QFile loadFile(fileName);
    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file config.json.");
    }
    QByteArray byte_json = loadFile.readAll();
    loadFile.close();

    m_msg = QString::fromLatin1(byte_json);

//    qDebug()<<m_msg;

}

Widget::~Widget()
{
    delete ui;
    delete m_ipc1;
//    delete m_ipc2;

//    m_ipc1->deleteLater();
    m_ipc1 = nullptr;
//    m_ipc2->deleteLater();

//    delete m_ipc3;
//    delete m_ipc4;

//    delete m_ipc5;
//    delete m_ipc6;

//    delete m_ipc7;
//    delete m_ipc8;

//    delete m_ipc9;
//    delete m_ipc10;

}

void Widget::sltRecvMsg(const QString &str)
{
    ui->textEdit->append("udpReceive111111::"+str);
}
void Widget::sltRecvMsg1(const QString &str)
{
    ui->textEdit->append("udpReceive22222::"+str);
}


void Widget::on_pushButton_clicked()
{
    qDebug()<<"Client send msg";
//    QString extraStr = "12323123123412341234asadf adsf asdfaada d"
//                       "ad adf adsf asdf asdf asdf asdf adfasdfasdfasddddddddddddddddf"
//                       "asdf asdf asdf asd adfasdfasdfasdfasdfasfdddddddddddddd"
//                       "asdf asdf asdf asdf adgasdfasdad adf asdf asdf asdf asdf asdf f"
//                       "asdf asdf asdf adgasdf asdf adfasdfddddddddddddddddddddddddd"
//                       "asdf asdf asdf adfgagasdf asdfadsfad asd fasdf asd  a"
//                       "adfgasdgasgfadsfasdfasdfasdasdfasdfddddddddddddddddddddddddddddddddd "
//                       "adsfadsf asd adffasdfasdfasdf asdf asasd asd asd d "
//                       "asdf asadfadsfasdfasdfasdfasdfasdfasdfdf asasd asd asd df "
//                       "asdf asdf asd asd sdf asdf asdf asdf asdfgadasd asd asd asd g"
//                       "agagag asdf asdf dfasdf asdfasdf asdf asdf asdf asd asd asd asd asd asd asd ads asdf asdf ";
    QString extraStr = m_msg;
    QString strInfo = extraStr + "Client send msg ===========";
    static int num = 1;
//    for(int i = 0 ; i< 100; i++)
    {
        m_ipc1->sentInfo(QString("%1%2").arg(strInfo).arg(num));
        num++;
    }

    // delay 3s
//    QTime t;
//    t.start();
//    while(t.elapsed()<3000){}
}
