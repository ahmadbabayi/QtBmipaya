#ifndef CHEQUEPRINT_H
#define CHEQUEPRINT_H

#include <QMainWindow>
#include <QPrintPreviewDialog>
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include <QTextDocument>

namespace Ui {
class ChequePrint;
}

class ChequePrint : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChequePrint(QString ersalname, QString ersalbabat, QWidget *parent = nullptr);
    ~ChequePrint();

private slots:
    void print(QPrinter *printer);

    void on_TarixEdit_returnPressed();

    void on_MablaghEdit_returnPressed();

    void on_DarvachEdit_returnPressed();

    void on_BabetEdit_returnPressed();

    void on_KodemelliEdit_returnPressed();

    void on_ExitButton_clicked();

    void on_PrintButton_clicked();

    void on_MablaghEdit_textEdited(const QString &arg1);

private:
    Ui::ChequePrint *ui;
};

#endif // CHEQUEPRINT_H
