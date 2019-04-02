#ifndef HHBASEDIALOG_H
#define HHBASEDIALOG_H
#include "hhbaseclass_global.h"

#include <QDialog>
class QMouseEvent;
class QHBoxLayout;
class QFrame;
class QGraphicsDropShadowEffect;

class HHBASECLASSSHARED_EXPORT HHBaseDialog : public QDialog
{
    Q_OBJECT
public:
    explicit HHBaseDialog(QWidget *parent = nullptr, bool bSupportShadow = true);
    virtual ~HHBaseDialog();

    //设置中心区域Widget
    void setCenterWidget(QWidget *p);
    //设置震动效果阴影颜色
    void setShadowColor(QColor color);
    //设置阴影是否有效
    void setShadowValid(bool bValid);

private:
    //窗口震动特效
    void changeDialogEffect(bool active);
    void initWidgetShadow();
    void initWidthNoShadow();

protected:
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    double                    m_dScaleFactor;
    QGraphicsDropShadowEffect *m_shadow_effect;
    QHBoxLayout               *m_frameLayout;
    QFrame                    *m_shadow_frame;
    bool                      m_bPressFlag;
    bool                      m_bShadowValid;
    QPoint                    m_beginDrag;
    bool                      m_bActive;
};

#endif // HHBASEDIALOG_H
