#ifndef SETTING_H
#define SETTING_H

#include <QMainWindow>
#include <QRegularExpressionValidator>
#include <QMessageBox>
#include <QtSql>

namespace Ui {
class Setting;
}

class Setting : public QMainWindow
{
    Q_OBJECT

public:
    explicit Setting(QWidget *parent = nullptr);
    ~Setting();

private slots:
    void SettingReload();
    bool sehv();

    void on_NameEdit_returnPressed();

    void on_ShebaEdit_returnPressed();

    void on_TelEdit_returnPressed();

    void on_AddressEdit_returnPressed();

    void on_KodemelliEdit_returnPressed();

    void on_BranchEdit_returnPressed();

    void on_ExitButton_clicked();

    void on_SaveButton_clicked();

    void on_BranchCodeEdit_returnPressed();

    void on_NameNomayandeEdit_returnPressed();

    void on_KodemelliNomayandeEdit_returnPressed();

private:
    Ui::Setting *ui;
};

#endif // SETTING_H
