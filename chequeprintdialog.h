#ifndef CHEQUEPRINTDIALOG_H
#define CHEQUEPRINTDIALOG_H

#include <QDialog>

namespace Ui {
class ChequePrintDialog;
}

class ChequePrintDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChequePrintDialog(QWidget *parent = nullptr);
    ~ChequePrintDialog();

private slots:
    void on_TarixEdit_returnPressed();

    void on_MablaghEdit_returnPressed();

    void on_DarvachEdit_returnPressed();

    void on_BabetEdit_4_returnPressed();

    void on_KodemelliEdit_returnPressed();

    void on_ExitButton_clicked();

private:
    Ui::ChequePrintDialog *ui;
};

#endif // CHEQUEPRINTDIALOG_H
