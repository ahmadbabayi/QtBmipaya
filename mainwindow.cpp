#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->ErsalSeri->setValidator( new QIntValidator);

    QDir *datadir = new QDir();
    if (!datadir->exists("data")){
        datadir->mkdir("data");
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("data/bmipaya.db");
        if (db.open()){
            QSqlQuery query;
            query.exec("create table paya (id INTEGER PRIMARY KEY AUTOINCREMENT, sheba TEXT, shenaseh TEXT, name TEXT, mablagh TEXT, sharh TEXT)");
            db.close();
        }
    }
    if (!dbopen()){
        qDebug() << ("Error");
    }
    TableReload();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Sheba_returnPressed()
{
    QWidget::focusNextChild();
}


void MainWindow::on_Name_returnPressed()
{
    QWidget::focusNextChild();
}


void MainWindow::on_Mablagh_returnPressed()
{
    QWidget::focusNextChild();
}


void MainWindow::on_Sharh_returnPressed()
{
    QWidget::focusNextChild();
}


void MainWindow::on_ErsalSheba_returnPressed()
{
    QWidget::focusNextChild();
}


void MainWindow::on_ErsalName_returnPressed()
{
    QWidget::focusNextChild();
}


void MainWindow::on_ErsalSeri_returnPressed()
{
    QWidget::focusNextChild();
}


void MainWindow::on_ErsalSharh_returnPressed()
{
    ui->Sheba->setFocus();
}


void MainWindow::on_SabtButton_clicked()
{
    QSqlQuery query;
    query.exec("INSERT INTO paya (sheba,shenaseh,name,mablagh,sharh) VALUES ('"+ui->Sheba->text()+"','"+ui->Shenaseh->text()+"','"+ui->Name->text()+"','"+ui->Mablagh->text()+"','"+ui->Sharh->text()+"')");

    ui->Sheba->setFocus();
    ui->Sheba->setText("");
    ui->Shenaseh->setText("");
    ui->Name->setText("");
    ui->Mablagh->setText("");
    TableReload();
}


void MainWindow::on_Shenaseh_returnPressed()
{
    QWidget::focusNextChild();
}


void MainWindow::on_SabtButton_pressed()
{

}


void MainWindow::on_RemoveButton_clicked()
{
    QSqlQuery query;
    query.exec("DELETE FROM paya");
    query.exec("DELETE FROM sqlite_sequence");
    TableReload();
}
void MainWindow::TableReload(){
    if (!dbopen()){
        qDebug() << ("Error");
    }
   QSqlQueryModel *model = new QSqlQueryModel;
   model->setQuery("SELECT sheba, shenaseh, name, mablagh, sharh FROM paya");
   model->setHeaderData(0, Qt::Horizontal, tr("شماره شبا"));
   model->setHeaderData(1, Qt::Horizontal, tr("شناسه واریز"));
   model->setHeaderData(2, Qt::Horizontal, tr("نام و نام خانوادگی"));
   model->setHeaderData(3, Qt::Horizontal, tr("مبلغ"));
   model->setHeaderData(4, Qt::Horizontal, tr("شرح"));
   ui->tableView->resizeColumnsToContents();
   ui->tableView->resizeRowsToContents();
   ui->tableView->setModel(model);
}

