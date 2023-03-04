#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QtSql>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QSqlDatabase mydb;
    void dbclose(){
        mydb.close();
        mydb.removeDatabase(QSqlDatabase::defaultConnection);
    }
    bool dbopen(){
        mydb = QSqlDatabase::addDatabase("QSQLITE");
        mydb.setDatabaseName("data/bmipaya.db");
        if (!mydb.open()){
            qDebug() << ("Failed to open database");
            return false;
        }
        else {
            return true;
        }
    }

private slots:
    void on_Sheba_returnPressed();

    void on_Name_returnPressed();

    void on_Mablagh_returnPressed();

    void on_Sharh_returnPressed();

    void on_ErsalSheba_returnPressed();

    void on_ErsalName_returnPressed();

    void on_ErsalSeri_returnPressed();

    void on_ErsalSharh_returnPressed();

    void on_SabtButton_clicked();

    void on_Shenaseh_returnPressed();

    void on_SabtButton_pressed();

    void on_RemoveButton_clicked();
    void TableReload();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
