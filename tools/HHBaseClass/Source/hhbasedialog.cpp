#include "hhbasedialog.h"
#include <QGraphicsDropShadowEffect>
#include <QApplication>
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QFrame>
#include <QDebug>

#include "Windows.h"

HHBaseDialog::HHBaseDialog(QWidget *parent , bool bSupportShadow) : QDialog(parent),
    m_bPressFlag(false),
    m_bShadowValid(true),
    m_bActive(false)
{
    setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);

    m_dScaleFactor = 1.0;
    QVariant value = QApplication::instance()->property("scalefactor");
    if(value.isValid())
    {
        m_dScaleFactor = value.toDouble();
    }
    if(bSupportShadow){
        initWidgetShadow();
    }else{
        initWidthNoShadow();
    }
}

HHBaseDialog::~HHBaseDialog()
{

}

void HHBaseDialog::initWidgetShadow()
{
    setAttribute(Qt::WA_TranslucentBackground);

    m_shadow_frame  = new QFrame(this);
    m_shadow_frame->setObjectName("background");

    m_shadow_frame->setStyleSheet("QFrame#background{border:1px solid lightgray; border-radius:4px; background-color:#ffffff}");
    m_frameLayout = new  QHBoxLayout(m_shadow_frame);
    m_frameLayout->setContentsMargins(0,0,0,0);
    m_frameLayout->setSpacing(0);

    m_shadow_effect = new QGraphicsDropShadowEffect(this);
    m_shadow_effect->setOffset(0, 0); //设定在哪个方向产生阴影效果
    m_shadow_effect->setColor(QColor( 0xd9d9d9 ));
    m_shadow_effect->setBlurRadius(10*m_dScaleFactor); //设定阴影的模糊度
    m_shadow_frame->setGraphicsEffect(m_shadow_effect);

    QHBoxLayout *backLayout = new  QHBoxLayout(this);
    backLayout->setContentsMargins(5*m_dScaleFactor,5*m_dScaleFactor,5*m_dScaleFactor,5*m_dScaleFactor);
    backLayout->setSpacing(0);
    backLayout->addWidget(m_shadow_frame);
}

void HHBaseDialog::initWidthNoShadow()
{
    m_shadow_frame  = new QFrame(this);
    m_shadow_frame->setObjectName("back");

    m_shadow_frame->setStyleSheet("QWidget#back{border:1px solid lightgray; border-radius:4px; background-color:#ffffff}");
    m_frameLayout = new  QHBoxLayout(m_shadow_frame);
    m_frameLayout->setContentsMargins(0,0,0,0);
    m_frameLayout->setSpacing(0);

    QHBoxLayout *backLayout = new  QHBoxLayout(this);
    backLayout->setContentsMargins(0,0,0,0);
    backLayout->setSpacing(0);
    backLayout->addWidget(m_shadow_frame);
}


void HHBaseDialog::setCenterWidget(QWidget *p)
{
    m_frameLayout->addWidget(p);
}

void HHBaseDialog::setShadowColor(QColor color)
{

}

void HHBaseDialog::setShadowValid(bool bValid)
{
    m_bShadowValid = bValid;
}

void HHBaseDialog::changeDialogEffect(bool active)
{
    QRect rect = this->geometry();
    if(m_bActive == active) return;
    m_bActive = active;
    int nWidth = (m_dScaleFactor>=1)? 2*m_dScaleFactor : 2;
    int nHeight = 0;
    if(active)
    {
        this->move(rect.x()-nWidth, rect.y()-nHeight);
    }else{
        this->move(rect.x()+nWidth, rect.y()+nHeight);
    }
}

bool HHBaseDialog::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    if(m_bShadowValid){
        MSG *msg = static_cast< MSG * >( message );
        if( msg->message == WM_NCACTIVATE)
        {
            bool active = (bool)(msg->wParam);
            changeDialogEffect(active);
            return false;
        }
    }
    return QDialog::nativeEvent(eventType, message, result);
}

void HHBaseDialog::mousePressEvent(QMouseEvent *event){
    m_bPressFlag = true;
    m_beginDrag = event->pos();
    QWidget::mousePressEvent(event);
}

void HHBaseDialog::mouseMoveEvent(QMouseEvent *event){
    if (m_bPressFlag) {
        QPoint relaPos(QCursor::pos() - m_beginDrag);
        move(relaPos);
    }
    QWidget::mouseMoveEvent(event);
}

void HHBaseDialog::mouseReleaseEvent(QMouseEvent *event){
    m_bPressFlag = false;
    QWidget::mouseReleaseEvent(event);
}
