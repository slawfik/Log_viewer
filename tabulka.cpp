#include "tabulka.h"
#include "ui_tabulka.h"

tabulka::tabulka(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tabulka)
{
    ui->setupUi(this);
}

tabulka::~tabulka()
{
    delete ui;
}
