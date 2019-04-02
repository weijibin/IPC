#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mydialog.h"
#include "mydialogqml.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    MyDialog *p = new MyDialog(this);
    p->exec();
}

void MainWindow::on_pushButton_3_clicked()
{
    QMLQialog  *p = new QMLQialog(this);
    p->exec();
}
