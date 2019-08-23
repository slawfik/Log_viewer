#include "log_pars.h"
#include "ui_log_pars.h"
#include <QObject>
#include <QCloseEvent>
#include <qobject.h>
//########################
#include <QDebug>
#include <QFileDialog>
#include <QAbstractItemModel>
#include <QDirIterator>

log_pars::log_pars(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::log_pars)
{
    stat_path = "";
    predchadzajuca_stat_path = stat_path;
    myModel = nullptr;
    myManualModel = nullptr;
    //ui->FIND_FILE->setStyleSheet("QPushButton#FIND_FILE { background-color: red }");
    /*QPalette pal;
    pal.setColor(QPalette::Active, QPalette::Button, Qt::green);
    pal.setColor(QPalette::Inactive, QPalette::Button, Qt::red);
    ui->FIND_FILE->setPalette(pal);*/
    ui->setupUi(this);
}

log_pars::~log_pars()
{
    if(this->myModel != nullptr)
        delete this->myModel;       //instancia parsera uvolnuje pamat správ z vektora
    if(this->myManualModel != nullptr){
        this->myManualModel->clearVector();
        delete  this->myManualModel;
    }
    if(predchadzajuce_datumy.size() != 0){
       clear_format_table_vitget(&predchadzajuce_datumy);
    }
    delete ui;
}


void log_pars::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Vyp app",
                                                                tr("Really nigga ?\n"),
                                                                QMessageBox::No | QMessageBox::Yes,
                                                                QMessageBox::No);
    if (resBtn != QMessageBox::Yes) {
        event->ignore();
    } else {
        event->accept();
    }
}

void log_pars::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_F1){
        this->on_PBtn_find_stat_path_clicked();
        //ui->statusbar->showMessage("F6 is perssed",5000);
    }
}

/*
bool log_pars::event(QEvent *event)
{
    if(event->KeyPress)
    {
        return false;
    }
}*/

void log_pars::on_FIND_FILE_clicked()
{
    //action_instance.set_combox(ui->cb_open_file); /*directory_watcher*/
    //ui->FIND_FILE->setStyleSheet("QPushButton#FIND_FILE:checked {color:black; background-color: green;}");
    //SET_PATH
    dir_path = QFileDialog::getExistingDirectory(this, "Open Directory", getenv("HOME"), QFileDialog::ShowDirsOnly);
    //QFileDialog tomas;

    //tomas.setOptions()
    qDebug() << dir_path << "---";
    if(dir_path.toStdString().compare("") != 0){
        if(ui->cb_open_file->count() > 0)   {
            std::cout <<"\nChex_box_count:__" << ui->cb_open_file->count() << endl;
            ui->cb_open_file->clear();
        }
        //_______________________________________test
        QDirIterator directories(dir_path, QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
        while(directories.hasNext()){
            directories.next();
            //qDebug() << directories.fileName();
            ui->cb_open_file->addItem(directories.fileName());
        }
        //_______________________________________end_test

        //SET_WATCHER
        /*watcher.addPath(dir_path);
        //QStringList directoryList = watcher.directories();
        QObject::connect(&watcher,SIGNAL(directoryChanged(QString)),&action_instance,SLOT(showModified(QString)));*/
        //SET_status_bar
        ui->label_log_msg_path->setText(dir_path);
        ui->statusbar->showMessage(dir_path);
   }
}

void log_pars::on_cb_open_file_currentIndexChanged(const QString &arg1)
{
    //___START INIT LOCAL VARIABLES___
    int r,m,d;
    string substr;
    string pom;
    QDate *date;
    QDir dir;
    QFileInfoList list;
    //static vector<QDate*> predchadzajuce_datumy;
    QTextCharFormat format;
    //___END INIT LOCAL VARIABLES___
    format.setBackground(QColor(184, 228, 186, 190));

    if(ui->cb_open_file->count() > 0) {        
        dir_path_final = dir_path +"/"+ arg1;
        ui->statusbar->showMessage(dir_path_final);
        if(predchadzajuce_datumy.size() != 0){
           clear_format_table_vitget(&predchadzajuce_datumy);
        }

        dir.setPath(dir_path_final);
        list = dir.entryInfoList(QDir::NoDotAndDotDot | QDir::Files, QDir::Time);
        Q_FOREACH(QFileInfo file, list){
            qDebug() << file.baseName();
            pom = file.baseName().toStdString();
            try {
                substr = pom.substr(0,4);
                substr.operator+=("\0");
                r = stoi(substr);
                substr = pom.substr(4,2);
                substr.operator+=("\0");
                m = stoi(substr);
                substr = pom.substr(6,2);
                substr.operator+=("\0");
                d = stoi(substr);

                date = new QDate(r,m,d);
                predchadzajuce_datumy.push_back(date);
                ui->calendarWidget->setDateTextFormat(*date,format);

                qDebug() << "d=" << QString::number(d) << " m=" << QString::number(m) << " r=" << QString::number(r);
            } catch (const std::exception& e) {
                qDebug() << "In decode file:" << file.baseName() << "__" << QString(e.what());
            }
        }
        dir_path_final = dir_path_final + "/";
    }
}

void log_pars::on_btn_clear_table_clicked()
{
    ui->statusbar->showMessage("Table is clean!",1000);
    if(myManualModel != nullptr){
        myManualModel->clearVector();                   //uvolní v?etky alokované správy vo vektore
        delete myManualModel;
        myManualModel = nullptr;
        qDebug() << "delete myManualModel!";
    }
}

void log_pars::on_pushButton_clicked()
{
    vector<string> list;
    string msg;

    if(myManualModel == nullptr){
        myManualModel = new my_tManual_model;
        qDebug() << "alocate myManualModel!";
    }
    string raw_data_string = ui->plainTextEdit->toPlainText().toLocal8Bit().constData();
    if (raw_data_string.back() != '\n'){            //rozdelujeme text podla zalomeni riadkov
            raw_data_string.append("\n");
    }
    list = rozdel_spravy(raw_data_string);

    for(size_t i = 0;i<list.size();i++){
        msg = list.operator[](i);
        if(is_good_formath_log_msg(msg)){
            qDebug() <<"arr.size" << static_cast<int>(myManualModel->arr->size()) << QString::fromStdString(msg);

            myManualModel->newMessage(msg);

            if(ui->tableView_manual->model() == nullptr){
                ui->tableView_manual->setModel(myManualModel);
                ui->tableView_manual->setColumnWidth(0,70);
                ui->tableView_manual->setColumnWidth(1,70);
                ui->tableView_manual->setColumnWidth(2,70);
                ui->tableView_manual->setColumnWidth(3,70);
                ui->tableView_manual->setColumnWidth(4,75);
                ui->tableView_manual->setColumnWidth(5,200);
            }
        }
    }
}

void log_pars::on_calendarWidget_clicked(const QDate &date)
{
    char bufer[50];
    int den = -1,mesiac = -1,rok = -1;
    string filename;

    if (ui->cb_open_file->count() > 0){
        date.getDate(&rok,&mesiac,&den);
        if(den < 10 && mesiac < 10){
            sprintf(bufer,"%d0%d0%d.bin",rok,mesiac,den);
        } else if(den < 10){
            sprintf(bufer,"%d%d0%d.bin",rok,mesiac,den);
        } else if (mesiac < 10) {
            sprintf(bufer,"%d0%d%d.bin",rok,mesiac,den);
        }
        filename.operator+=(dir_path_final.toLatin1().toStdString());
        filename.operator+=(bufer);
        qDebug() << QString::fromStdString(filename);
        ui->statusbar->showMessage(QString::fromStdString(filename));
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

               ui->tableView->setColumnWidth(0,70);
               ui->tableView->resizeColumnToContents(TRI);
               QString msg = QString::fromLatin1("Bolo spracovaných %1 logových správ.")
                       .arg(QString::number(myModel->inst_of_parser.arr->size()));
               ui->statusbar->showMessage(msg);
    }
}

void log_pars::clear_format_table_vitget(vector<QDate*> *date_vector){
    QTextCharFormat format;
    //___END INIT LOCAL VARIABLES___
    format.setBackground(Qt::white);
    for(size_t i =0;i<date_vector->size();i++){
        ui->calendarWidget->setDateTextFormat(*date_vector->operator[](i),format);
        delete date_vector->operator[](i);
    }
    date_vector->clear();
}

bool log_pars::is_good_formath_log_msg(string pa_string){
    //______TEST_VALIDITY_SPRAVY___
    size_t poz = pa_string.find(":");
    if(poz == std::string::npos){
        poz = pa_string.find(".");
        if(poz == std::string::npos){
            ui->statusbar->showMessage(QString("Zly format zspravy"),4000);
            return false;
        }
    }
    if(poz+LEN_LOG_BODY > pa_string.length())   {
        qDebug() << poz+LEN_LOG_BODY << "  " << pa_string.length();
        ui->statusbar->showMessage(QString("Zly format spravy"),4000);
        return false;
    }
    return true;
    //______TEST_VALIDITY_SPRAVY___
}

vector<string> log_pars::rozdel_spravy(string list_sprav){
    vector<string> list;
    size_t posl;
    string pomString;

    size_t posf = list_sprav.find("\n");
    if (posf != std::string::npos){
        list.push_back(list_sprav.substr(0,posf));
        posl = list_sprav.find("\n",posf+1,1);
        while (posl != std::string::npos){
            list.push_back(list_sprav.substr(posf,posl-posf));
            posf = posl;
            posl = list_sprav.find("\n",posf+1,1);
        }
    }
    return list;
    //qDebug() << "1 " <<QString::fromStdString(list.operator[](0)) << "2 " << QString::fromStdString(list.operator[](1));
}

void log_pars::on_PBtn_find_stat_path_clicked()
{
    QString pa_path;
    pa_path = QFileDialog::getOpenFileName(this,tr("Open .bin file"),"C:/Users/","All files (*.bin*)");
    if(pa_path.toStdString().compare("") != 0){
        predchadzajuca_stat_path = stat_path;
        stat_path = pa_path;
        QPalette pal;
        pal.setColor(QPalette::Active, QPalette::Button, Qt::green);
        pal.setColor(QPalette::Inactive, QPalette::Button, Qt::green);
        ui->PBtn_find_stat_path->setPalette(pal);

        if (!stat_parser.run_parser(stat_path)){
            QString msg = QString::fromLatin1("Nepodarilo sa otvori? súbor ") + stat_path;
            return;
        }

        QString msg = QString::fromLatin1("Nastavený súbor ") + stat_path;
        ui->statusbar->showMessage(msg,4000);
    } else{
        QString msg = QString::fromLatin1("Nebol nastavený správny súbor!");
        ui->statusbar->showMessage(msg,3000);
    }
}

void log_pars::on_btn_export_excel_clicked()
{
    if(stat_parser.msgVector_is_full()){
        wchar_t fileName[30] = L"all_tele_stat.xls";
        write_excel *xls_writer = new write_excel();
        xls_writer->month_stat = ui->checkBox_month_stat->isChecked();
        //je potrebná zamedzi? opetovnému po?ítaniu mesa?ných statistík lebo by sa duplikovali
        if(xls_writer->month_stat && stat_path.compare(predchadzajuca_stat_path) != 0){
            predchadzajuca_stat_path = stat_path;
            qDebug() << "Calc_month stat!";
            stat_parser.setup_calc_month_MSG();
        }
        xls_writer->createExcel_file(xls_writer->month_stat);
        xls_writer->write_data(stat_parser.get_msg_vector());
        xls_writer->saveExcel_file(fileName);
        delete xls_writer;
        QMessageBox::information(this,"Export", "Created excel file!");
    }   else{
        QMessageBox::critical(this,"Export", "Please select .bin file with statistic data or press F1 !");
    }
}

