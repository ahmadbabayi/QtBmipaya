#ifndef CHEQUEVAGOZARI_H
#define CHEQUEVAGOZARI_H

#include <QMainWindow>
#include <QMessageBox>
#include <QtSql>
#include <QInputDialog>
#include <QPrintPreviewDialog>
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include <QTextDocument>

namespace Ui {
class ChequeVagozari;
}

class ChequeVagozari : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChequeVagozari(QWidget *parent = nullptr);
    ~ChequeVagozari();
    bool virayesh = false;
    int id;

private slots:
    bool sehv();
    void TableReload();
    void Print(QPrinter *printer);

    void on_pushButton_clicked();

    void on_TarixEdit_returnPressed();

    void on_SerialEdit_returnPressed();

    void on_HesabEdit_returnPressed();

    void on_BankEdit_returnPressed();

    void on_BranchEdit_returnPressed();

    void on_MablaghEdit_returnPressed();

    void on_MablaghEdit_textEdited(const QString &arg1);

    void on_EditButton_clicked();

    void on_RemoveButton_clicked();

    void on_PrintButton_clicked();

private:
    Ui::ChequeVagozari *ui;
};

#endif // CHEQUEVAGOZARI_H
