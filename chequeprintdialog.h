#ifndef CHEQUEPRINTDIALOG_H
#define CHEQUEPRINTDIALOG_H

#include <QDialog>
#include <QPrintPreviewDialog>
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include <QTextDocument>

namespace Ui {
class ChequePrintDialog;
}

class ChequePrintDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChequePrintDialog(QString ersalname, QString ersalbabat, QWidget *parent = nullptr);
    ~ChequePrintDialog();

private slots:
    void print(QPrinter *printer);

    void on_TarixEdit_returnPressed();

    void on_MablaghEdit_returnPressed();

    void on_DarvachEdit_returnPressed();

    void on_KodemelliEdit_returnPressed();

    void on_ExitButton_clicked();

    void on_MablaghEdit_textEdited(const QString &arg1);

    void on_BabetEdit_returnPressed();

    void on_PrintButton_clicked();

private:
    Ui::ChequePrintDialog *ui;
};

#endif // CHEQUEPRINTDIALOG_H
