#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QObject>
#include <math.h>

class Functions : public QObject
{
    Q_OBJECT
public:
    explicit Functions(QObject *parent = nullptr);
    QString InsertComma(QString s);
    QString InsertZero(QString s, int k);
    bool ShebaCheck(QString s);

signals:

};

#endif // FUNCTIONS_H
