#ifndef LOG_PARS_H
#define LOG_PARS_H

#include <QMainWindow>
#include "qtablewidget.h"
#include "directory_watcher_action.h"
#include "my_t_model.h"
#include "my_tmanual_model.h"
#include "write_excel.h"

namespace Ui {
class log_pars;
}

class log_pars : public QMainWindow
{
    Q_OBJECT

public:
    vector<QDate*> predchadzajuce_datumy;

    //QFileSystemWatcher watcher;
    //directory_watcher_action action_instance;
    statistic_msg_parser stat_parser;
    My_T_model* myModel;
    my_tManual_model* myManualModel;

    explicit log_pars(QWidget *parent = nullptr);
    ~log_pars();

private slots:

    void keyPressEvent(QKeyEvent *event);

    void closeEvent(QCloseEvent *event);

    //bool event(QEvent *event);

    void on_FIND_FILE_clicked();

    void on_cb_open_file_currentIndexChanged(const QString &arg1);

    void on_btn_clear_table_clicked();

    void on_pushButton_clicked();

    void on_calendarWidget_clicked(const QDate &date);

    void on_PBtn_find_stat_path_clicked();

    void on_btn_export_excel_clicked();

private:
    QString predchadzajuca_stat_path;
    QString stat_path;
    QString dir_path;
    QString dir_path_final;

    Ui::log_pars *ui;
    vector<string> rozdel_spravy(string list_sprav);
    void clear_format_table_vitget(vector<QDate*> *date_vector);
    bool is_good_formath_log_msg(string pa_string);
};

#endif // LOG_PARS_H
