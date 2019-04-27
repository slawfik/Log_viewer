#include "log_pars.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    log_pars w;
    //Table tab;
    w.show();

    return a.exec();
}
