#include "my_tmanual_model.h"
#include <QFont>
#include <QBrush>
#include <QDebug>

my_tManual_model::my_tManual_model(QObject *parent)
    : QAbstractTableModel(parent)
{
    arr = new vector<Mesage *>();
}

int my_tManual_model::rowCount(const QModelIndex & /*parent*/) const
{
   return static_cast<int>(arr->size());
   qDebug() << "call.size !" << arr->size();
}

int my_tManual_model::columnCount(const QModelIndex & /*parent*/) const
{
    return 6;
}

QVariant my_tManual_model::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return QString("Tele");
        case 1:
            return QString("Datum");
        case 2:
            return QString("Cas");
        case 3:
            return QString("Priorita");
        case 4:
            return QString("Autor spravy");
        case 5:
            return QString(" Telo spravy");
        }
    }/* else if (role == Qt::SizeHintRole && orientation == Qt::Horizontal){
        switch (section) {
        case 0:
            return QSize(10,30);
        case 1:
            return QSize(1000,50);
        case 2:
            return QSize(1000,50);
        case 3:
            return QSize(1000,50);
        case 4:
            return QSize(1000,50);
        case 5:
            return QSize(1000,50);
        }
    }*/
    return QVariant();
}

QVariant my_tManual_model::data(const QModelIndex &index, int role) const
{

    unsigned int row = static_cast<unsigned int>(index.row());
    unsigned int col =static_cast<unsigned int>(index.column());
    // generate a log message when this method gets called
    //qDebug() << QString("row %1, col%2, role %3").arg(row).arg(col).arg(role);

    switch (role) {
        case Qt::DisplayRole:
            if (col == 0) return QString(QString::fromStdString(arr->operator[](row)->getS_tele()));
            else if (col == 1) return QString(QString::fromStdString(arr->operator[](row)->getS_date()));
            else if (col == 2) return QString(QString::fromStdString(arr->operator[](row)->getS_time()));
            else if (col == 3) return QString(QString::fromStdString(arr->operator[](row)->getS_flag()));
            else if (col == 4) return QString(QString::fromStdString(arr->operator[](row)->getS_priority()));
            else if (col == 5) return QString(QString::fromStdString(arr->operator[](row)->getS_body()));
            else               return QString("");

        case Qt::FontRole:
            /*if (row == 0 && col == 0) { //change font only for cell(0,0)
                QFont boldFont;
                boldFont.setBold(true);
                return boldFont;
            }*/
            break;
        case Qt::BackgroundRole:
            switch (arr->operator[](row)->getPriority()) {
                case 1:
                    return QBrush(Qt::green);
                case 2:
                    return QBrush(Qt::yellow);
                case 3:
                    return QBrush(Qt::red);
            }
            break;
        /*case Qt::TextAlignmentRole:
            if (row == 1 && col == 1) //change text alignment only for cell(1,1)
                return Qt::AlignRight + Qt::AlignVCenter;
            break;
        case Qt::CheckStateRole:
            if (row == 1 && col == 0) //add a checkbox to cell(1,0)
                return Qt::Checked;
            break;*/
    }
    return QVariant();
}

void my_tManual_model::newMessage(string pa_message){
    int row = static_cast<int>(arr->size());
    beginInsertRows(QModelIndex(), row, row);
    arr->push_back(new Mesage(pa_message));
    endInsertRows();
}

void my_tManual_model::clearVector(){
    for(size_t i=0; i<arr->size();i++){
        delete arr->operator[](i);
    }
    this->arr->clear();
}
