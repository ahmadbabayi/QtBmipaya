#ifndef CHEQUEVAGOZARI_H
#define CHEQUEVAGOZARI_H

#include <QMainWindow>
#include <QMessageBox>
#include <QtSql>

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

private slots:
    bool sehv();
    void TableReload();

    void on_pushButton_clicked();

    void on_TarixEdit_returnPressed();

    void on_SerialEdit_returnPressed();

    void on_HesabEdit_returnPressed();

    void on_BankEdit_returnPressed();

    void on_BranchEdit_returnPressed();

    void on_MablaghEdit_returnPressed();

private:
    Ui::ChequeVagozari *ui;
};

#endif // CHEQUEVAGOZARI_H
