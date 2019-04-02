#include "mydialogqml.h"
#include <QVBoxLayout>
#include <QQuickWidget>
#include <QQmlContext>
#include <QPushButton>

QMLQialog::QMLQialog(QWidget *parent)
    : HHBaseDialog(parent)
{
    this->setFixedSize(700,500);
    QQuickWidget *m_pView = new QQuickWidget(this);
    m_pView->rootContext()->setContextProperty("setting", this);
    m_pView->setSource(QUrl(QStringLiteral("qrc:/customsettingqml/HHToolTip.qml")));

    setShadowColor(QColor(0x74AEDA));
    setCenterWidget(m_pView);
}

void QMLQialog::mousePressEvent(QMouseEvent *event)
{
    this->reject();
}
