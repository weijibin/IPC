#include "widget.h"
#include <QApplication>
#include <QFile>
#include <QSettings>
#include <QMutex>
#include <QDir>
#include <QDateTime>

void outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    static QMutex mutex;
    mutex.lock();
    // get log path from version.ini
#ifdef Q_OS_ANDROID
    QSettings settings("envDir:/version.ini",QSettings::IniFormat);
#else
    QSettings settings(QApplication::applicationDirPath() + "/version.ini",QSettings::IniFormat);
#endif
    settings.setIniCodec("UTF-8");
    settings.beginGroup("Log");
#ifdef Q_OS_LINUX
    QString strLogPath = settings.value("UnixPath","/home/hht/HiteTouchPro_Log").toString();
#else
    QString strLogPath = settings.value("Path","C:/ProgramData/HiClass/HiteTouchPro/Log").toString();
#endif
    QString strLogLevel = settings.value("Level","Debug").toString();
    settings.endGroup();
    QString strLogFileName;
    QDir dirLog(strLogPath);
    if(!dirLog.exists())
        dirLog.mkpath(strLogPath);

    QString strBuf = QString("log_%1.txt").arg(QDateTime::currentDateTime().toString("MM-dd_hhmm"));
    if(!dirLog.exists())
        strLogFileName = strBuf;
    else
        strLogFileName = QString("%1/%2").arg(strLogPath).arg(strBuf);

    int nLevel = 3;
    if( QString::compare( strLogLevel, "info", Qt::CaseInsensitive ) == 0 )
        nLevel = 4;
    QString text;
    switch(type)
    {
    case QtInfoMsg:
        text = QString("Info:");
        break;
    case QtDebugMsg:
        text = QString("Debug:");
        break;
    case QtWarningMsg:
        text = QString("Warning:");
        break;
    case QtCriticalMsg:
        text = QString("Critical:");
        break;
    case QtFatalMsg:
        text = QString("Fatal:");
    }
    if(type > nLevel)
    {
        mutex.unlock();
        return;
    }
    QString context_info = QString("(%1 %2)").arg(QString(context.file)).arg(context.line);
    QString current_date_time = QDateTime::currentDateTime().toString("hh:mm:ss zzz"); //"yyyy-MM-dd hh:mm:ss ddd"
    QString current_date = QString("%1").arg(current_date_time);
    QString message = QString("%1 %2 %3 %4").arg(current_date).arg(text).arg(msg).arg(context_info);

    QFile file(strLogFileName);
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream text_stream(&file);
    text_stream << message << "\r\n";
    file.flush();
    file.close();

    mutex.unlock();
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    qInstallMessageHandler(outputMessage);

    Widget w;
    w.show();

    return a.exec();
}
