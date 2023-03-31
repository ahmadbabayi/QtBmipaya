#include "setting.h"
#include "ui_setting.h"
#include "database.h"

Setting::Setting(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Setting)
{
    ui->setupUi(this);
}

Setting::~Setting()
{
    delete ui;
}
