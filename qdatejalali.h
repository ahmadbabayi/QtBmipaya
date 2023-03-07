#ifndef QDATEJALALI_H
#define QDATEJALALI_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QTime>

class QDateJalali : public QObject
{
    Q_OBJECT
public:
    explicit QDateJalali(QObject *parent = nullptr);
    int div(int a,int b);
    QStringList ToShamsi(QString year, QString month,QString day );
    QString JalaliDate();

signals:

};

#endif // QDATEJALALI_H
