#ifndef NUM2STR_H
#define NUM2STR_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>

class Num2Str
{
public:
    Num2Str();
    QString Adad2Huruf(QString s);
    QString InsertZero(QString s, int k);
    QString Sadqan(QString s);
};

#endif // NUM2STR_H
