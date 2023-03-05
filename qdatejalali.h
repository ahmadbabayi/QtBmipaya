#ifndef QDATEJALALI_H
#define QDATEJALALI_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>

class QDateJalali : public QObject
{
    Q_OBJECT
public:
    explicit QDateJalali(QObject *parent = nullptr);
    int div(int a,int b);
    QStringList ToShamsi(QString year, QString month,QString day );

signals:

};

#endif // QDATEJALALI_H
