#include "chequevagozari.h"
#include "ui_chequevagozari.h"
#include "numberformatdelegate.h"
#include "qdatejalali.h"
#include "database.h"

ChequeVagozari::ChequeVagozari(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChequeVagozari)
{
    ui->setupUi(this);

    ui->SerialEdit->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]*")));
    ui->HesabEdit->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]*")));

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
            //query.exec("UPDATE payavagozari SET sheba = '"+ui->Sheba->text()+"', shenaseh = '"+ui->Shenaseh->text()+"', name = '"+ui->Name->text()+"', mablagh = '"+ui->Mablagh->text().replace(",","")+"', sharh = '"+ui->Sharh->text()+"' WHERE id ="+ QString::number(id));
        }
        else{
            query.exec("INSERT INTO payavagozari (tarix, serial, hesab, bank, branch, mablagh) VALUES ('"+ui->TarixEdit->text()+"','"+ui->SerialEdit->text()+"','"+ui->HesabEdit->text()+"','"+ui->BankEdit->text().replace(",","")+"','"+ui->BranchEdit->text()+"','"+ui->MablaghEdit->text()+"')");
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

