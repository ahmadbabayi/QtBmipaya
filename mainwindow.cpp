#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->ErsalSeri->setValidator( new QIntValidator);
    ui->ErsalSheba->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]*")));
    ui->Sheba->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]*")));
    ui->Shenaseh->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]*")));

    QDir *datadir = new QDir();
    if (!datadir->exists("data")){
        datadir->mkdir("data");
            }
    if (!QFile::exists("data/bmipaya.db")){
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("data/bmipaya.db");
        if (db.open()){
            QSqlQuery query;
            query.exec("create table paya (id INTEGER PRIMARY KEY AUTOINCREMENT, sheba TEXT, shenaseh TEXT, name TEXT, mablagh TEXT, sharh TEXT)");
            query.exec("create table payaersal (id INTEGER PRIMARY KEY, sheba TEXT, seri TEXT, name TEXT, sharh TEXT)");
            query.exec("INSERT INTO payaersal (id, sheba, seri, name, sharh) VALUES (1,'','','','')");
            db.close();
            db.removeDatabase(QSqlDatabase::defaultConnection);
        }
    }

    if (!dbopen()){
        QMessageBox msgBox; msgBox.setText("Database Error."); msgBox.exec();
    }
    ErsalReload();
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
   QSqlQueryModel *model = new QSqlQueryModel;
   model->setQuery("SELECT sheba, shenaseh, name, mablagh, sharh FROM paya");
   model->setHeaderData(0, Qt::Horizontal, tr("شماره شبا"));
   model->setHeaderData(1, Qt::Horizontal, tr("شناسه واریز"));
   model->setHeaderData(2, Qt::Horizontal, tr("نام و نام خانوادگی"));
   model->setHeaderData(3, Qt::Horizontal, tr("مبلغ"));
   model->setHeaderData(4, Qt::Horizontal, tr("شرح"));
   ui->tableView->setModel(model);
   ui->tableView->resizeColumnsToContents();
   ui->tableView->resizeRowsToContents();
}

void MainWindow::ErsalReload(){
    QSqlQuery query;
    query.exec("SELECT * FROM payaersal WHERE id =1");
    while (query.next()) {
            ui->ErsalSheba->setText(query.value(1).toString());
            ui->ErsalSeri->setText(query.value(2).toString());
            ui->ErsalName->setText(query.value(3).toString());
            ui->ErsalSharh->setText(query.value(4).toString());
    }
}

void MainWindow::on_ErsalSheba_textChanged(const QString &arg1)
{
    QSqlQuery query;
    query.exec("UPDATE payaersal SET sheba = '"+ui->ErsalSheba->text()+"' WHERE id =1");
}


void MainWindow::on_ErsalSeri_textChanged(const QString &arg1)
{
    QSqlQuery query;
    query.exec("UPDATE payaersal SET seri = '"+ui->ErsalSeri->text()+"' WHERE id =1");
}


void MainWindow::on_ErsalName_textChanged(const QString &arg1)
{
    QSqlQuery query;
    query.exec("UPDATE payaersal SET name = '"+ui->ErsalName->text()+"' WHERE id =1");
}


void MainWindow::on_ErsalSharh_textChanged(const QString &arg1)
{
    QSqlQuery query;
    query.exec("UPDATE payaersal SET sharh = '"+ui->ErsalSharh->text()+"' WHERE id =1");
}

