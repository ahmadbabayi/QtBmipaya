#include "setting.h"
#include "ui_setting.h"
#include "database.h"
#include "functions.h"

Setting::Setting(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Setting)
{
    ui->setupUi(this);

    ui->NameEdit->setFocus();
    ui->ShebaEdit->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]*")));
    ui->KodemelliEdit->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]*")));
    ui->KodemelliNomayandeEdit->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]*")));
    ui->BranchCodeEdit->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]*")));
    SettingReload();
}

Setting::~Setting()
{
    delete ui;
}

void Setting::SettingReload(){
    QSqlQuery query;
    query.exec("SELECT * FROM payasetting WHERE id =1");
    while (query.next()) {
            ui->NameEdit->setText(query.value(1).toString());
            ui->ShebaEdit->setText(query.value(2).toString());
            ui->TelEdit->setText(query.value(3).toString());
            ui->AddressEdit->setText(query.value(4).toString());
            ui->KodemelliEdit->setText(query.value(5).toString());
            ui->NameNomayandeEdit->setText(query.value(6).toString());
            ui->KodemelliNomayandeEdit->setText(query.value(7).toString());
            ui->BranchEdit->setText(query.value(8).toString());
            ui->BranchCodeEdit->setText(query.value(9).toString());
    }
}

bool Setting::sehv(){
    bool xata=true;
    Functions *func = new Functions();
    if (!func->ShebaCheck(ui->ShebaEdit->text())){
        xata = false;
        QMessageBox msgBox; msgBox.setText("شماره شبا نادرست می‌باشد! "); msgBox.exec();
        ui->ShebaEdit->setFocus();
    }
    return xata;
}

void Setting::on_NameEdit_returnPressed()
{
    QWidget::focusNextChild();
}


void Setting::on_ShebaEdit_returnPressed()
{
    QWidget::focusNextChild();
}


void Setting::on_TelEdit_returnPressed()
{
    QWidget::focusNextChild();
}


void Setting::on_AddressEdit_returnPressed()
{
    QWidget::focusNextChild();
}


void Setting::on_KodemelliEdit_returnPressed()
{
    QWidget::focusNextChild();
}


void Setting::on_BranchEdit_returnPressed()
{
    QWidget::focusNextChild();
}

void Setting::on_BranchCodeEdit_returnPressed()
{
    QWidget::focusNextChild();
}


void Setting::on_ExitButton_clicked()
{
    Setting::close();
}


void Setting::on_SaveButton_clicked()
{
    if (sehv()){
        QSqlQuery query;
        query.exec("UPDATE payasetting SET name = '"+ui->NameEdit->text()+"', sheba = '"+ui->ShebaEdit->text()+"', tel = '"+ui->TelEdit->text()+"', address = '"+ui->AddressEdit->text()+"', kodemelli = '"+ui->KodemelliEdit->text()+"', namenomayande = '"+ui->NameNomayandeEdit->text()+"', kodemellinomayande = '"+ui->KodemelliNomayandeEdit->text()+"', branchname = '"+ui->BranchEdit->text()+"', branchcode = '"+ui->BranchCodeEdit->text()+"' WHERE id =1");
        QMessageBox msgBox; msgBox.setText("اطلاعات ذخیره گردید."); msgBox.exec();
    }
}





void Setting::on_NameNomayandeEdit_returnPressed()
{
    QWidget::focusNextChild();
}


void Setting::on_KodemelliNomayandeEdit_returnPressed()
{
    QWidget::focusNextChild();
}

