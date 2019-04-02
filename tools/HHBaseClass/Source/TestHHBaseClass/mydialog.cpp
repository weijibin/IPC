#include "mydialog.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>

MyDialog::MyDialog(QWidget *parent): HHBaseDialog(parent)
{
    int nShadowWidth = 5;
    this->setFixedSize(700+nShadowWidth,500+nShadowWidth);

    QWidget *pBackWidget = new QWidget(this);
    pBackWidget->setObjectName("pBackWidget");
    pBackWidget->setStyleSheet("QWidget#pBackWidget{border-radius:4px; background-color:white}");

    QPushButton *pBtn = new QPushButton(pBackWidget);
    pBtn->setFixedSize(70,40);
    pBtn->setText("BTN1");
    QPushButton *pBtn2 = new QPushButton(pBackWidget);
    pBtn2->setText("CLOSE");
    pBtn2->setFixedSize(50,40);
    QPushButton *pBtn3 = new QPushButton(pBackWidget);
    pBtn3->setText("BTN3");
    pBtn3->setFixedSize(70,40);

    connect(pBtn2, SIGNAL(clicked(bool)), this, SLOT(reject()));

    //对pBackWidget做布局
    QHBoxLayout *backLayout = new  QHBoxLayout(pBackWidget);
    backLayout->setContentsMargins(0,0,0,0);
    backLayout->setSpacing(0);
    backLayout->addWidget(pBtn);
    backLayout->addWidget(pBtn2);
    backLayout->addWidget(pBtn3);

    //设置阴影颜色效果----白板采用绿色阴影效果，可不设置，其他软件如需定制颜色调用该接口
    // setShadowColor(QColor(0x74AEDA)); //例：0x74AEDA  蓝色
    //将实现类的中心QWidget传入基类
    setCenterWidget(pBackWidget);
}
