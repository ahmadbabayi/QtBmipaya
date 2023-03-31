#ifndef SETTING_H
#define SETTING_H

#include <QMainWindow>
#include "database.h"

namespace Ui {
class Setting;
}

class Setting : public QMainWindow
{
    Q_OBJECT

public:
    explicit Setting(QWidget *parent = nullptr);
    ~Setting();

private:
    Ui::Setting *ui;
};

#endif // SETTING_H
