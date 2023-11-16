#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <vector>

#include "screenrow.h"

class DbManager
{
public:
    DbManager( const QString& path );

    void addRow( const ScreenRow& screenRow );

    ScreenRow getRow( int index );

    int size();

private:
    QSqlDatabase db;
    std::vector< ScreenRow > rows;
};

#endif // DBMANAGER_H
