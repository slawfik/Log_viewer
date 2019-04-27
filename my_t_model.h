#ifndef MY_T_MODEL_H
#define MY_T_MODEL_H

#include <QAbstractTableModel>
#include "parser_inst.h"

class My_T_model : public QAbstractTableModel
{
    Q_OBJECT
public:
    parser_inst inst_of_parser;

    My_T_model(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
};

#endif // MY_T_MODEL_H
