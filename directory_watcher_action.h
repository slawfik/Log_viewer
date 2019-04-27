#ifndef DIRECTORY_WATCHER_ACTION_H
#define DIRECTORY_WATCHER_ACTION_H

#include <QMessageBox>
#include <QWidget>
#include <QFileSystemWatcher>
#include <QComboBox>
#include <QDir>
#include "qdebug.h"



class directory_watcher_action : public QWidget
{
    Q_OBJECT

public:
    QComboBox *combo_box;

    explicit directory_watcher_action(QWidget* parent=Q_NULLPTR)
        :QWidget(parent){}

    ~directory_watcher_action(){}

    void set_combox(QComboBox* pa_combo_box) {
        combo_box = pa_combo_box;
    }
public slots:
    void showModified(const QString& str)
    {
        //Q_UNUSED(str)
        QDir dir;
        dir.setPath(str);
        QFileInfoList list = dir.entryInfoList(QDir::NoDotAndDotDot | QDir::Files, QDir::Time);
        combo_box->clear();
        Q_FOREACH(QFileInfo _list, list){
            qDebug() << _list.baseName();
            combo_box->addItem(_list.baseName());
        }

        QMessageBox::information(this,"Directory Modified", "Your Directory is modified lease refresh log file.");
    }
};

#endif // DIRECTORY_WATCHER_ACTION_H
