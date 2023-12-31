#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "dbmanager.h"
#include "imagecomparator.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void prntScr();

protected:
    void timerEvent(QTimerEvent *event);

private:
    void addRow( const ScreenRow& screenRow );

    void addRow( const ScreenRow& screenRow, const QPixmap& winScr );

private:
    Ui::MainWindow * ui;
    DbManager dbManager;
    ImageComparator imageComparator;
    QPixmap prevScr;
    int timerId;

    int count = 0; // TODO: Temporary solution for saving img
};
#endif // MAINWINDOW_H
