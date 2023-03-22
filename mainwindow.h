#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QtSql>
#include <QFile>
#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>
#include <QPrintPreviewDialog>
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include <QTextDocument>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool virayesh = false;
    int id=0,tedad;
    QString sum;
    QString InsertComma(QString s);

    QSqlDatabase mydb;
    void dbclose(){
        mydb.close();
        mydb.removeDatabase(QSqlDatabase::defaultConnection);
    }
    bool dbopen(){
        mydb = QSqlDatabase::addDatabase("QSQLITE");
        mydb.setDatabaseName("BmiPaya_data/bmipaya.db");
        if (!mydb.open()){
            qDebug() << ("Failed to open database");
            return false;
        }
        else {
            return true;
        }
    }

private slots:
    void TableReload();
    void ErsalReload();
    void SumTedad();
    bool ShebaCheck(QString s);
    QString InsertZero(QString s, int k);
    void print(QPrinter *printer);
    void printD(QPrinter *printer);
    bool sehv();
    bool ErsalSehv();

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

    void on_RemoveButton_clicked();

    void on_ErsalSheba_textChanged(const QString &arg1);

    void on_ErsalSeri_textChanged(const QString &arg1);

    void on_ErsalName_textChanged(const QString &arg1);

    void on_ErsalSharh_textChanged(const QString &arg1);

    void on_PrintdButton_clicked();

    void on_EditButton_clicked();

    void on_PrintButton_clicked();

   void on_Mablagh_textEdited(const QString &arg1);

   void on_MakeButton_clicked();

   void on_ExcelExport_triggered();

   void on_Excelmport_triggered();

   void on_HelpAction_triggered();

   void on_AboutAction_triggered();

   void on_ExitAction_triggered();

   void on_RestoerAction_triggered();

   void on_SearchEdit_textChanged(const QString &arg1);

   void on_PrintCheque_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
