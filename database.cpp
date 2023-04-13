#include "database.h"

Database::Database(QObject *parent)
    : QObject{parent}
{

}

void Database::dbcreate(){
    QDir *datadir = new QDir();
    if (!datadir->exists("BmiPaya_data")){
        datadir->mkdir("BmiPaya_data");
    }
    if (!QFile::exists("BmiPaya_data/bmipayayeni.db")){
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("BmiPaya_data/bmipayayeni.db");
        if (db.open()){
            QSqlQuery query;
            query.exec("create table paya (id INTEGER PRIMARY KEY AUTOINCREMENT, sheba TEXT, shenaseh TEXT, name TEXT, mablagh TEXT, sharh TEXT)");
            query.exec("create table payaersal (id INTEGER PRIMARY KEY, sheba TEXT, seri TEXT, name TEXT, sharh TEXT)");
            query.exec("INSERT INTO payaersal (id, sheba, seri, name, sharh) VALUES (1,'','','','')");
            query.exec("create table payasetting (id INTEGER PRIMARY KEY, name TEXT, sheba TEXT, tel TEXT, address TEXT, kodeposti TEXT, kodemelli TEXT, namenomayande TEXT, kodemellinomayande TEXT, branchname TEXT, branchcode TEXT)");
            query.exec("INSERT INTO payasetting (id, name, sheba, tel, address, kodeposti, kodemelli, namenomayande, kodemellinomayande, branchname, branchcode) VALUES (1,'','','','','','','','','','')");
            query.exec("create table payavagozari (id INTEGER PRIMARY KEY AUTOINCREMENT, tarix TEXT, serial TEXT, hesab TEXT, bank TEXT, branch TEXT, mablagh TEXT, shenaseh TEXT)");
            db.close();
            db.removeDatabase(QSqlDatabase::defaultConnection);
        }
    }
}

bool Database::dbopen(){
    mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("BmiPaya_data/bmipayayeni.db");
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
