#include "chequeprintdialog.h"
#include "ui_chequeprintdialog.h"
#include "qdatejalali.h"
#include "num2str.h"
#include "mainwindow.h"

ChequePrintDialog::ChequePrintDialog(QString ersalname, QString ersalbabat, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChequePrintDialog)
{
    MainWindow *mainwindow = new MainWindow();
    QString sum = mainwindow->sum;
    ui->setupUi(this);
    QDateJalali tarix;
    ui->TarixEdit->setText(tarix.JalaliTarix());
    ui->MablaghEdit->setText(mainwindow->InsertComma(sum));

    Num2Str s;
    QString h;
    h = s.Adad2Huruf(sum);
    ui->hlabel->setText(h);

    ui->DarvachEdit->setText(ersalname);
    ui->BabetEdit->setText(ersalbabat);
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


void ChequePrintDialog::on_MablaghEdit_textEdited(const QString &arg1)
{
    MainWindow *mainwindow = new MainWindow();
    ui->MablaghEdit->setText(mainwindow->InsertComma(ui->MablaghEdit->text().replace(",","")));
    QString sum = mainwindow->sum; Num2Str s; QString h; h = s.Adad2Huruf(ui->MablaghEdit->text().replace(",","")); ui->hlabel->setText(h);
}


void ChequePrintDialog::on_BabetEdit_returnPressed()
{
    QWidget::focusNextChild();
}

