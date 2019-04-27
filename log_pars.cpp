#include "log_pars.h"
#include "ui_log_pars.h"
#include <QObject>
#include <qobject.h>
//########################
#include <QDebug>
#include <QFileDialog>

log_pars::log_pars(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::log_pars)
{
    myModel = nullptr;
    ui->setupUi(this);
}

log_pars::~log_pars()
{
    if(this->myModel != nullptr)
        delete this->myModel;
    delete ui;
}

void log_pars::on_FIND_FILE_clicked()
{
    action_instance.set_combox(ui->cb_open_file);
    //SET_PATH
    dir_path = QFileDialog::getExistingDirectory(this, "Open Directory", getenv("HOME"), QFileDialog::ShowDirsOnly);
    //SET_comboBox
    qDebug() << dir_path << "---";
    if(dir_path.toStdString().compare("") != 0){
        if(ui->cb_open_file->count() > 0)   {
            std::cout <<"\nChex_box_count:__" << ui->cb_open_file->count() << endl;
            ui->cb_open_file->clear();
        }
        QDir dir;
        dir.setPath(dir_path);
        QFileInfoList list = dir.entryInfoList(QDir::NoDotAndDotDot | QDir::Files, QDir::Time);
        Q_FOREACH(QFileInfo directory, list){
            ui->cb_open_file->addItem(directory.baseName());
        }
        //SET_WATCHER
        watcher.addPath(dir_path);
        QStringList directoryList = watcher.directories();
        QObject::connect(&watcher,SIGNAL(directoryChanged(QString)),&action_instance,SLOT(showModified(QString)));
        //SET_status_bar
        ui->button_directory->setText(dir_path);
        ui->statusbar->showMessage(dir_path);
   }
}

void log_pars::on_cb_open_file_currentIndexChanged(const QString &arg1)
{
    string filename;
    if(ui->cb_open_file->count() > 0) {
        filename = dir_path.toStdString() +"/"+ arg1.toStdString()+".txt";
        //_stare_//inst_of_parser.pars_message(filename);
        //cout << filename << std::endl;

        if(myModel == nullptr){
            myModel = new My_T_model;
            qDebug() << "alocate!";
        } else {
            delete  myModel;
            myModel = new My_T_model;
            qDebug() << "delete & alocate!";
        }
        myModel->inst_of_parser.pars_message(filename);
        ui->tableView->setModel(myModel);
        myModel->dataChanged(myModel->index(0,0),myModel->index(myModel->inst_of_parser.getMessage_count(),3));

        ui->tableView->resizeColumnToContents(TRI);
        ui->statusbar->showMessage(QString("Bolo spracovaných %1 logových správ.")
                                   .arg(QString::number(myModel->inst_of_parser.getMessage_count())));
    }
}

/*void log_pars::refresh_table()  {
    QString q_time, q_flag, q_priority, q_body;
    QStringList titulka;
    titulka << "Čas" << "Typ správy" << "Priorita" << "Telo";
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setHorizontalHeaderLabels(titulka);

    if(inst_of_parser.message_count > alocate_table_item){
        if(alocate_table_item == 0) {
            time_item = new QTableWidgetItem[inst_of_parser.message_count];
            flag_item = new QTableWidgetItem[inst_of_parser.message_count];
            prior_item = new QTableWidgetItem[inst_of_parser.message_count];
            body_item = new QTableWidgetItem[inst_of_parser.message_count];
            alocate_table_item = inst_of_parser.message_count;
        }   else {
            void* aaaa;
            aaaa = realloc(time_item,inst_of_parser.message_count*sizeof (QTableWidgetItem));
            time_item = (QTableWidgetItem*) aaaa;
            aaaa = realloc(flag_item,inst_of_parser.message_count*sizeof (QTableWidgetItem));
            flag_item = (QTableWidgetItem*) aaaa;
            aaaa = realloc(prior_item,inst_of_parser.message_count*sizeof (QTableWidgetItem));
            prior_item = (QTableWidgetItem*) aaaa;
            aaaa = realloc(body_item,inst_of_parser.message_count*sizeof (QTableWidgetItem));
            body_item = (QTableWidgetItem*) aaaa;
            for(int i = 0;i<inst_of_parser.message_count;i++){
                QTableWidgetItem* pom;
                pom = ui->tableWidget->takeItem(i,NULA);

                ui->tableWidget->setItem(i,NULA,NULL);
                ui->tableWidget->setItem(i,JEDEN,NULL);
                ui->tableWidget->setItem(i,DVA,NULL);
                ui->tableWidget->setItem(i,TRI,NULL);
            }//
            delete time_item;
            delete flag_item;
            delete prior_item;
            delete body_item;
            time_item = new QTableWidgetItem[inst_of_parser.message_count];
            flag_item = new QTableWidgetItem[inst_of_parser.message_count];
            prior_item = new QTableWidgetItem[inst_of_parser.message_count];
            body_item = new QTableWidgetItem[inst_of_parser.message_count];
            alocate_table_item = inst_of_parser.message_count;
        }

    }

    for(int i=0;i<inst_of_parser.message_count;i++)   {
        QTableView aa;
        QVariant();

        int row = ui->tableWidget->rowCount();
        q_time = QString::fromStdString(inst_of_parser._message[i]->getS_time());
        time_item[i].setText(q_time);
        q_flag = QString::fromStdString(inst_of_parser._message[i]->getS_flag());
        flag_item[i].setText(q_flag);
        q_priority = QString::fromStdString(inst_of_parser._message[i]->getS_priority());
        prior_item[i].setText(q_priority);
        q_body = QString::fromStdString(inst_of_parser._message[i]->getS_body());
        body_item[i].setText(q_body);

        ui->tableWidget->insertRow(row);

        switch (inst_of_parser._message[i]->getPriority()) {
            case 2:
                time_item[i].setBackgroundColor(Qt::yellow);
                flag_item[i].setBackgroundColor(Qt::yellow);
                prior_item[i].setBackgroundColor(Qt::yellow);
                body_item[i].setBackgroundColor(Qt::yellow);
                break;
            case 3:
                time_item[i].setBackgroundColor(Qt::red);
                flag_item[i].setBackgroundColor(Qt::red);
                prior_item[i].setBackgroundColor(Qt::red);
                body_item[i].setBackgroundColor(Qt::red);
                break;
        }
        ui->tableWidget->setItem(row,NULA,time_item+i);
        ui->tableWidget->setItem(row,JEDEN,flag_item+i);
        ui->tableWidget->setItem(row,DVA,prior_item+i);
        ui->tableWidget->setItem(row,TRI,body_item+i);
        ui->tableWidget->resizeColumnToContents(TRI);
            //ui->tableWidget->item(riadok,stlpec)
    }


    QModelIndex aa;
    //QVariant bb = myModel.data(aa);
    //myModel.setProperty("tomas",bb);



    ui->tableView->setModel(&myModel);
    aa = myModel.index(1,1,QModelIndex());
    QString tt = "tomas";
    myModel.setData(aa,tt);
}*/

