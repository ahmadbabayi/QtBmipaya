#include "chequevagozari.h"
#include "ui_chequevagozari.h"

ChequeVagozari::ChequeVagozari(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChequeVagozari)
{
    ui->setupUi(this);
}

ChequeVagozari::~ChequeVagozari()
{
    delete ui;
}
