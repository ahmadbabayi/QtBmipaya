#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QDebug>

class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QObject *parent = nullptr);
    QSqlDatabase mydb;
    bool dbopen();
    void dbclose();

signals:

};

#endif // DATABASE_H
