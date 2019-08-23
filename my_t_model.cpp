#include "my_t_model.h"
#include <QFont>
#include <QBrush>
#include <QDebug>

My_T_model::My_T_model(QObject *parent)
    : QAbstractTableModel(parent)
{

}

int My_T_model::rowCount(const QModelIndex & /*parent*/) const
{
   return static_cast<int>(inst_of_parser.arr->size());
}

int My_T_model::columnCount(const QModelIndex & /*parent*/) const
{
    return 4;
}

QVariant My_T_model::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return QString("Cas");
        case 1:
            return QString("Priorita");
        case 2:
            return QString("Autor spravy");
        case 3:
            return QString(" Telo spravy ");
        }
    }
    return QVariant();
}

QVariant My_T_model::data(const QModelIndex &index, int role) const
{

    unsigned int row = static_cast<unsigned int>(index.row());
    unsigned int col =static_cast<unsigned int>(index.column());
    // generate a log message when this method gets called
    //qDebug() << QString("row %1, col%2, role %3").arg(row).arg(col).arg(role);

    switch (role) {
        case Qt::DisplayRole:
            if (col == 0) return QString(QString::fromStdString(inst_of_parser.arr->operator[](row)->getS_time()));
            else if (col == 1) return QString(QString::fromStdString(inst_of_parser.arr->operator[](row)->getS_flag()));
            else if (col == 2) return QString(QString::fromStdString(inst_of_parser.arr->operator[](row)->getS_priority()));
            else if (col == 3) return QString(QString::fromStdString(inst_of_parser.arr->operator[](row)->getS_body()));
            else               return QString("");

        case Qt::FontRole:
            /*if (row == 0 && col == 0) { //change font only for cell(0,0)
                QFont boldFont;
                boldFont.setBold(true);
                return boldFont;
            }*/
            break;
        case Qt::BackgroundRole:
            switch (inst_of_parser.arr->operator[](row)->getPriority()) {
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

