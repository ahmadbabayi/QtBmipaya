#include "chequeprint.h"
#include "ui_chequeprint.h"
#include "qdatejalali.h"
#include "num2str.h"
#include "mainwindow.h"

ChequePrint::ChequePrint(QString ersalname, QString ersalbabat, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChequePrint)
{
    ui->setupUi(this);
    MainWindow *mainwindow = new MainWindow();
    QString sum = mainwindow->sum;
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

ChequePrint::~ChequePrint()
{
    delete ui;
}

void ChequePrint::on_TarixEdit_returnPressed()
{
    QWidget::focusNextChild();
}


void ChequePrint::on_MablaghEdit_returnPressed()
{
    QWidget::focusNextChild();
}


void ChequePrint::on_DarvachEdit_returnPressed()
{
    QWidget::focusNextChild();
}


void ChequePrint::on_BabetEdit_returnPressed()
{
    QWidget::focusNextChild();
}


void ChequePrint::on_KodemelliEdit_returnPressed()
{
    QWidget::focusNextChild();
}


void ChequePrint::on_ExitButton_clicked()
{
    ChequePrint::close();
}

void ChequePrint::on_MablaghEdit_textEdited(const QString &arg1)
{
    MainWindow *mainwindow = new MainWindow();
    ui->MablaghEdit->setText(mainwindow->InsertComma(ui->MablaghEdit->text().replace(",","")));
    QString sum = mainwindow->sum; Num2Str s; QString h; h = s.Adad2Huruf(ui->MablaghEdit->text().replace(",","")); ui->hlabel->setText(h);
}

void ChequePrint::on_PrintButton_clicked()
{
    QPrinter *printer = new QPrinter();
    printer->setFullPage(true);
    QPageSize pageSize(QPageSize::C5E);
    printer->setPageSize(pageSize);
    QPrintPreviewDialog *printPreview = new QPrintPreviewDialog(printer);
    connect(printPreview, SIGNAL(paintRequested(QPrinter*)), this, SLOT(print(QPrinter*)));
    printPreview->setWindowTitle("Preview Dialog");
    printPreview->exec();
}

void ChequePrint::print(QPrinter *printer)
{
    QString txt;

    MainWindow *mainwindow = new MainWindow();
    //QString sum = mainwindow->sum;
    Num2Str s;
    QString h;
    h = s.Adad2Huruf(ui->MablaghEdit->text().replace(",",""));

    txt="<html width=\"100%\"><head><style>body {direction: rtl; font-family: \"B Nazanin\", \"Times New Roman\", Tahoma; font-size: 16px; }</style></head>"
         "<body><table dir=\"rtl\" width=\"100%\" cellspacing=\"0\" cellpadding=\"3\">"
            "<tr>"
            "<td colspan=\"3\" style=\"text-indent: 150px\">"+ui->TarixEdit->text()+"</td>"
            "</tr>"
            "<tr>"
            "<td colspan=\"3\" style=\"text-indent: 170px\">"+h+" ریال##</td>"
            "</tr>"
            "<tr><td colspan=\"3\">&nbsp;</td></tr>"
            "</tr>"
            "<tr>"
            "<td colspan=\"3\" style=\"text-indent: 80px\">"+ui->DarvachEdit->text()+" بابت "+ui->BabetEdit->text()+" شناسه ملی "+ui->KodemelliEdit->text()+"</td>"
            "</tr>"
            "<tr><td colspan=\"3\">&nbsp;</td></tr>"
            "<tr><td colspan=\"3\">&nbsp;</td></tr>"
            "<tr>"
            "<td>&nbsp;</td>"
            "<td align=\"left\" colspan=\"2\">##"+mainwindow->InsertComma(ui->MablaghEdit->text().replace(",",""))+"##</td>"
            "</tr>"
            "</table></body></html>";
    QTextDocument document;
    //document.setDocumentMargin(0.1);
        document.setHtml(txt);
        document.print(printer);
}


