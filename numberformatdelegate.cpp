#include "numberformatdelegate.h"

NumberFormatDelegate::NumberFormatDelegate(QObject *parent) :
QStyledItemDelegate(parent)
{
}

QString NumberFormatDelegate::displayText(const QVariant &value, const QLocale &locale) const
{
    QLocale::setDefault(QLocale::English);
    QLocale ss;
    QString str;
    str = ss.toString(value.toLongLong());
    return str;
}
