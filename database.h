#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QtSql>
#include <QDebug>
#include <QDir>

class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QObject *parent = nullptr);
    QSqlDatabase mydb;
    void dbcreate();
    bool dbopen();
    void dbclose();

signals:

};

#endif // DATABASE_H
