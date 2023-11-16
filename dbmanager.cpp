#include "dbmanager.h"

#include <QSqlQuery>
#include <QVariant>

#include <iostream>

DbManager::DbManager( const QString& path )
{
    db = QSqlDatabase::addDatabase( "QSQLITE" );
    db.setDatabaseName( path );

    if ( db.open() )
    {
        QSqlQuery query( db );
        query.exec(
            "CREATE TABLE screens (image_path TEXT, hash_sum TEXT, percent FLOAT);"
        );

        query.exec("SELECT * FROM screens;");
        while (query.next()) {
            ScreenRow screenRow;

            screenRow.path = query.value(0).toString();
            screenRow.hashSum = query.value(1).toString();
            screenRow.percent = query.value(1).toFloat();

            rows.push_back( screenRow );
        }
    }
    else
    {
       //qDebug() << "Database: connection ok";
    }
}

void DbManager::addRow( const ScreenRow& screenRow )
{
    QSqlQuery query( db );
    query.prepare("INSERT INTO screens VALUES (:path, :hash, :percent)");
    query.bindValue(":path", screenRow.path);
    query.bindValue(":hash", screenRow.hashSum);
    query.bindValue(":percent", screenRow.percent);

    if(!query.exec())
    {
         /*qDebug() << "addPerson error:"
                  << query.lastError();*/
    }
}

ScreenRow DbManager::getRow( int index )
{
    return rows[index];
}

int DbManager::size()
{
    return rows.size();
}
