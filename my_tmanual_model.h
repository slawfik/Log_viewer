#ifndef MY_TMANUAL_MODEL_H
#define MY_TMANUAL_MODEL_H

#include <QAbstractTableModel>
#include "mesage.h"

class my_tManual_model : public QAbstractTableModel
{
    Q_OBJECT
public:
    vector<Mesage *> * arr;

    void newMessage(string pa_message);
    void clearVector();

    my_tManual_model(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
};
#endif // MY_TMANUAL_MODEL_H
