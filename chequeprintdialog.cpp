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


void ChequePrintDialog::on_KodemelliEdit_returnPressed()
{
    QWidget::focusNextChild();
}


void ChequePrintDialog::on_ExitButton_clicked()
{
    //QApplication::exit();
    ChequePrintDialog::close();
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


void ChequePrintDialog::on_PrintButton_clicked()
{
    QPrinter *printer = new QPrinter();
    printer->setFullPage(true);
    QPageSize pageSize(QPageSize::A4);
    printer->setPageSize(pageSize);
    QPrintPreviewDialog *printPreview = new QPrintPreviewDialog(printer);
    connect(printPreview, SIGNAL(paintRequested(QPrinter*)), this, SLOT(print(QPrinter*)));
    printPreview->setWindowTitle("Preview Dialog");
    printPreview->exec();
}

void ChequePrintDialog::print(QPrinter *printer)
{
    QString txt;

    MainWindow *mainwindow = new MainWindow();
    QString sum = mainwindow->sum;
    Num2Str s;
    QString h;
    h = s.Adad2Huruf(sum);

    txt="<html width=\"100%\"><head><style>body {direction: rtl; font-family: \"B Nazanin\", \"Times New Roman\", Tahoma; } table, th, td {border: 1px solid black; border-collapse: collapse;}</style></head>"
         "<table dir=\"rtl\" width=\"100%\" cellspacing=\"0\" cellpadding=\"3\">"
            "<tr>"
            "<td colspan=\"3\">"+ui->TarixEdit->text()+"</td>"
            "</tr>"
            "<tr>"
            "<td colspan=\"3\">"+h+"</td>"
            "</tr>"
            "</tr>"
            "<tr>"
            "<td>شناسه ملی "+ui->KodemelliEdit->text()+"</td><td>بابت "+ui->BabetEdit->text()+"</td><td>"+ui->DarvachEdit->text()+"</td>"
            "</tr>"
            "<tr>"
            "<td align=\"left\" colspan=\"3\">"+mainwindow->InsertComma(sum)+"</td>"
            "</tr>"
            "</table>";
    QTextDocument document;
    //document.setDocumentMargin(0.1);
        document.setHtml(txt);
        document.print(printer);
}

