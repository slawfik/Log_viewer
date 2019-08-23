#include "log_pars.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    log_pars w;
    //Table tab;
    w.show();
    w.setWindowTitle("Log message parser");
    w.setWindowIcon(QIcon("resources/parse2.ico"));

    return a.exec();
}
