#include "chequeprintdialog.h"
#include "ui_chequeprintdialog.h"
#include "qdatejalali.h"

ChequePrintDialog::ChequePrintDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChequePrintDialog)
{
    ui->setupUi(this);
    QDateJalali tarix;
    ui->TarixEdit->setText(tarix.JalaliTarix());
}

ChequePrintDialog::~ChequePrintDialog()
{
    delete ui;
}

void ChequePrintDialog::on_TarixEdit_returnPressed()
{
    QWidget::focusNextChild();
}


void ChequePrintDialog::on_MablaghEdit_returnPressed()
{
    QWidget::focusNextChild();
}


void ChequePrintDialog::on_DarvachEdit_returnPressed()
{
    QWidget::focusNextChild();
}


void ChequePrintDialog::on_BabetEdit_4_returnPressed()
{
    QWidget::focusNextChild();
}


void ChequePrintDialog::on_KodemelliEdit_returnPressed()
{
    QWidget::focusNextChild();
}


void ChequePrintDialog::on_ExitButton_clicked()
{
    QApplication::exit();
}

