#ifndef TABULKA_H
#define TABULKA_H

#include <QWidget>
#include <QTableWidget>

namespace Ui {
class tabulka;
}

class tabulka : public QWidget
{
    Q_OBJECT

public:

    QTableWidget tab;
    explicit tabulka(QWidget *parent = nullptr);
    ~tabulka();

private:
    Ui::tabulka *ui;
};

#endif // TABULKA_H
