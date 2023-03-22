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
    QString JalaliDate();
    QString JalaliTarix();
    QString InsertZero(QString s, int k);
    QStringList gregorian_to_jalali(long gy, long gm, long gd);

signals:

};

#endif // QDATEJALALI_H
