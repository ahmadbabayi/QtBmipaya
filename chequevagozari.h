#ifndef CHEQUEVAGOZARI_H
#define CHEQUEVAGOZARI_H

#include <QMainWindow>

namespace Ui {
class ChequeVagozari;
}

class ChequeVagozari : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChequeVagozari(QWidget *parent = nullptr);
    ~ChequeVagozari();

private:
    Ui::ChequeVagozari *ui;
};

#endif // CHEQUEVAGOZARI_H
