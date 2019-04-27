#ifndef LOG_PARS_H
#define LOG_PARS_H

#include <QMainWindow>
#include "qtablewidget.h"
#include "directory_watcher_action.h"
#include "my_t_model.h"

namespace Ui {
class log_pars;
}

class log_pars : public QMainWindow
{
    Q_OBJECT

public:
    QString dir_path;
    QFileSystemWatcher watcher;
    directory_watcher_action action_instance;
    My_T_model* myModel;

    explicit log_pars(QWidget *parent = nullptr);
    ~log_pars();

private slots:

    void on_FIND_FILE_clicked();

    void on_cb_open_file_currentIndexChanged(const QString &arg1);

private:

    Ui::log_pars *ui;
    //void refresh_table();
};

#endif // LOG_PARS_H
