#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDesktopWidget>
#include <QTableWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableWidget->setColumnCount(1);

    timerId = startTimer(1000000);
}

MainWindow::~MainWindow()
{
    killTimer(timerId);
    delete ui;
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    prntScr();
}

void MainWindow::prntScr()
{
    QPixmap winScr = QPixmap::grabWindow(
        QApplication::desktop()->winId()
    );

    QTableWidgetItem *thumbnail = new QTableWidgetItem;
    thumbnail->setData( Qt::DecorationRole, winScr );

    ui->tableWidget->insertRow( ui->tableWidget->rowCount() );

    ui->tableWidget->setItem(
            ui->tableWidget->rowCount() - 1
        ,   0
        ,   thumbnail
    );
}
