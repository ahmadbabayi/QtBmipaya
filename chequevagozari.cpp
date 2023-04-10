#include "chequevagozari.h"
#include "ui_chequevagozari.h"
#include "numberformatdelegate.h"
#include "qdatejalali.h"
#include "database.h"
#include "functions.h"

ChequeVagozari::ChequeVagozari(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChequeVagozari)
{
    ui->setupUi(this);

    ui->SerialEdit->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]*")));
    ui->HesabEdit->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]*")));
    ui->TarixEdit->setInputMask("0000/00/00");

    Database db;
    if (!db.dbopen()){
        QMessageBox msgBox; msgBox.setText("Database Error."); msgBox.exec();
    }
    TableReload();
}

ChequeVagozari::~ChequeVagozari()
{
    delete ui;
}

bool ChequeVagozari::sehv(){
    bool xata=true;
    if(ui->MablaghEdit->text() == ""){
        xata = false;
        QMessageBox msgBox; msgBox.setText("مبلغ چک الزامی می باشد! "); msgBox.exec();
        ui->MablaghEdit->setFocus();
    }
    if (ui->BankEdit->text() == ""){
        xata = false;
        QMessageBox msgBox; msgBox.setText("نام بانک عهده چک الزامی می باشد! "); msgBox.exec();
        ui->BankEdit->setFocus();
    }
    if (ui->HesabEdit->text() == ""){
        xata = false;
        QMessageBox msgBox; msgBox.setText("شماره حساب چک الزامی می باشد! "); msgBox.exec();
        ui->HesabEdit->setFocus();
    }
    if (ui->SerialEdit->text() == ""){
        xata = false;
        QMessageBox msgBox; msgBox.setText("سریال چک الزامی می باشد! "); msgBox.exec();
        ui->SerialEdit->setFocus();
    }
    if(ui->TarixEdit->text() == ""){
        xata = false;
        QMessageBox msgBox; msgBox.setText("تاریخ چک الزامی می باشد! "); msgBox.exec();
        ui->TarixEdit->setFocus();
    }
    return xata;
}

void ChequeVagozari::TableReload(){
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT * FROM payavagozari");

    model->setHeaderData(0, Qt::Horizontal, tr("ردیف"));
    model->setHeaderData(1, Qt::Horizontal, tr("تاریخ چک"));
    model->setHeaderData(2, Qt::Horizontal, tr("سریال چک"));
    model->setHeaderData(3, Qt::Horizontal, tr("شماره حساب چک"));
    model->setHeaderData(4, Qt::Horizontal, tr("بانک"));
    model->setHeaderData(5, Qt::Horizontal, tr("شعبه"));
    model->setHeaderData(6, Qt::Horizontal, tr("مبلغ"));
    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->setModel(model);
    ui->tableView->setItemDelegateForColumn(6, new NumberFormatDelegate(this));
    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();
}

void ChequeVagozari::on_pushButton_clicked()
{
    if (sehv()){
        QSqlQuery query;
        if (virayesh){
            query.exec("UPDATE payavagozari SET tarix = '"+ui->TarixEdit->text()+"', serial = '"+ui->SerialEdit->text()+"', hesab = '"+ui->HesabEdit->text()+"', bank = '"+ui->BankEdit->text()+"', branch = '"+ui->BranchEdit->text()+"', mablagh = '"+ui->MablaghEdit->text().replace(",","")+"' WHERE id ="+ QString::number(id));
        }
        else{
            query.exec("INSERT INTO payavagozari (tarix, serial, hesab, bank, branch, mablagh) VALUES ('"+ui->TarixEdit->text()+"','"+ui->SerialEdit->text()+"','"+ui->HesabEdit->text()+"','"+ui->BankEdit->text().replace(",","")+"','"+ui->BranchEdit->text()+"','"+ui->MablaghEdit->text().replace(",","")+"')");
        }

        ui->TarixEdit->setFocus();
        ui->TarixEdit->setText("");
        ui->SerialEdit->setText("");
        ui->HesabEdit->setText("");
        ui->BankEdit->setText("");
        ui->BranchEdit->setText("");
        ui->MablaghEdit->setText("");
        TableReload();
        ui->tableView->scrollToBottom();
        virayesh = false;
    }
}


void ChequeVagozari::on_TarixEdit_returnPressed()
{
    QWidget::focusNextChild();
}


void ChequeVagozari::on_SerialEdit_returnPressed()
{
    QWidget::focusNextChild();
}


void ChequeVagozari::on_HesabEdit_returnPressed()
{
    QWidget::focusNextChild();
}


void ChequeVagozari::on_BankEdit_returnPressed()
{
    QWidget::focusNextChild();
}


void ChequeVagozari::on_BranchEdit_returnPressed()
{
    QWidget::focusNextChild();
}


void ChequeVagozari::on_MablaghEdit_returnPressed()
{
    QWidget::focusNextChild();
}


void ChequeVagozari::on_MablaghEdit_textEdited(const QString &arg1)
{
    Functions func;
    QString str;
        str = func.InsertComma(ui->MablaghEdit->text().replace(",",""));
        ui->MablaghEdit->setText(str);
}


void ChequeVagozari::on_EditButton_clicked()
{
    bool ok;
    Functions func;
    id = QInputDialog::getInt(this, tr("ویرایش رکورد موجود در لیست"), tr("شماره ردیف را وارد کنید:"), 1, 1, 100000, 1, &ok);
    if (ok){
        QSqlQuery query;
        query.exec("SELECT * FROM payavagozari WHERE id =" + QString::number(id));
        while (query.next()) {
                ui->TarixEdit->setText(query.value(1).toString());
                ui->SerialEdit->setText(query.value(2).toString());
                ui->HesabEdit->setText(query.value(3).toString());
                ui->BankEdit->setText(query.value(4).toString());
                ui->BranchEdit->setText(query.value(5).toString());
                ui->MablaghEdit->setText(func.InsertComma(query.value(6).toString()));
                ui->TarixEdit->setFocus();
        }
     virayesh = true;
     }
}


void ChequeVagozari::on_RemoveButton_clicked()
{
    bool ok;
        id = QInputDialog::getInt(this, tr("حذف رکورد موجود در لیست"), tr("شماره ردیف را وارد کنید:"), 1, 1, 100000, 1, &ok);
        if (ok){
        QSqlQuery query;
        query.exec("DELETE FROM payavagozari WHERE id =" + QString::number(id));
        query.exec("UPDATE payavagozari SET id = (id -1) WHERE id > "+ QString::number(id));
        query.exec("DELETE FROM sqlite_sequence");

        TableReload();
        }
}


void ChequeVagozari::on_PrintButton_clicked()
{
    QPrinter *printer = new QPrinter();
    printer->setFullPage(true);
    QPageSize pageSize(QPageSize::A4);
    printer->setPageSize(pageSize);
    QPrintPreviewDialog *printPreview = new QPrintPreviewDialog(printer);
    connect(printPreview, SIGNAL(paintRequested(QPrinter*)), this, SLOT(Print(QPrinter*)));
    printPreview->setWindowTitle("Preview Dialog");
    printPreview->exec();
}

void ChequeVagozari::Print(QPrinter *printer){
        QString txt;
        QDateJalali Jalali;
        txt="<html width=\"100%\"><head><style>body {direction: rtl; font-family: \"B Nazanin\", \"Times New Roman\", Tahoma; font-size: 16px;}</style></head>"
                     "<body><div dir=\"rtl\"><div> :تاریخ "+Jalali.JalaliTarix()+"</div><div dir=\"rtl\"> :شماره</div>"
                        "</body></html>";
        QTextDocument document;
        document.setHtml(txt);
        document.print(printer);
}

