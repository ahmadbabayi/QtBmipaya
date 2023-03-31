#include "setting.h"
#include "ui_setting.h"
#include "database.h"

Setting::Setting(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Setting)
{
    ui->setupUi(this);
    ui->NameEdit->setFocus();
    ui->ShebaEdit->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]*")));
}

Setting::~Setting()
{
    delete ui;
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


void Setting::on_BranchKodEdit_returnPressed()
{
    QWidget::focusNextChild();
}

