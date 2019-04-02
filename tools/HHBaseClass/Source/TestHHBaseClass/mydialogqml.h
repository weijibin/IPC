#ifndef QMLQIDGET_H
#define QMLQIDGET_H

#include "../../include/hhbasedialog.h"

class QMLQialog : public HHBaseDialog
{
public:
    explicit QMLQialog(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event);
};

#endif // QMLQIDGET_H
