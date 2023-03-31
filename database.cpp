#include "database.h"

Database::Database(QObject *parent)
    : QObject{parent}
{

}

bool Database::dbopen(){
    mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("BmiPaya_data/bmipaya.db");
    if (!mydb.open()){
        qDebug() << ("Failed to open database");
        return false;
    }
    else {
        return true;
    }
}

void Database::dbclose(){
    mydb.close();
    mydb.removeDatabase(QSqlDatabase::defaultConnection);
}
