#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDesktopWidget>
#include <QTableWidget>
#include <QFile>

#include <iostream>

namespace
{
    static const int MILLISECONDS_IN_MINUTE = 60000;
    static const int COLUMN_COUNT = 3;
    static const int SCALE = 160;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , dbManager("screens.db")
{
    ui->setupUi(this);

    ui->tableWidget->setColumnCount(COLUMN_COUNT);

    for ( int i = 0; i < dbManager.size(); ++i )
        addRow( dbManager.getRow( i ) );

    timerId = startTimer(MILLISECONDS_IN_MINUTE);
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
    QString path = QString::number(++count) + ".png";

    QFile file(path);
    file.open(QIODevice::WriteOnly);

    QPixmap winScr = QPixmap::grabWindow(
        QApplication::desktop()->winId()
    );

    winScr.save(&file);

    ScreenRow screenRow( path, "SOME_HASH", 1 );
    dbManager.addRow( screenRow );

    addRow( screenRow, winScr );
}

void MainWindow::addRow( const ScreenRow& screenRow )
{
    addRow( screenRow, QPixmap( screenRow.path) );
}

void MainWindow::addRow( const ScreenRow& screenRow, const QPixmap& winScr )
{
    ui->tableWidget->insertRow( ui->tableWidget->rowCount() );

    QTableWidgetItem *thumbnail = new QTableWidgetItem;
    thumbnail->setData( Qt::DecorationRole, winScr.scaled(SCALE,SCALE,Qt::IgnoreAspectRatio) );
    ui->tableWidget->setItem(
            ui->tableWidget->rowCount() - 1
        ,   0
        ,   thumbnail
    );

    QTableWidgetItem *hashData = new QTableWidgetItem;
    hashData->setText( screenRow.hashSum );
    ui->tableWidget->setItem(
            ui->tableWidget->rowCount() - 1
        ,   1
        ,   hashData
    );

    QTableWidgetItem *percent = new QTableWidgetItem;
    percent->setText( QString::number( screenRow.percent ) );
    ui->tableWidget->setItem(
            ui->tableWidget->rowCount() - 1
        ,   2
        ,   percent
    );
}
