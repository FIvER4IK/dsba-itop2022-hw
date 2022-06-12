#ifndef NETFLIXMODEL_H
#define NETFLIXMODEL_H

#include <QAbstractTableModel>
#include <QTableView>
#include "storage.h"
//class NetflixModel : public QAbstractItemModel
//{
//    Q_OBJECT

//public:
//    explicit NetflixModel(QObject *parent = nullptr);

//    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
//    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
//    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;


//private:
//    QTableView netflixFilms;
//    QList<QList<QString>> dataTable;
//    QList<QString> headerList;
//};

class NetflixModel : public QAbstractTableModel
{
    Q_OBJECT
protected:
    Storage* _films;

public:
    explicit NetflixModel(Storage* films, QObject* parent = nullptr);

public:
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

public:
    QVariant data(const QModelIndex& indx, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

};

#endif // NETFLIXMODEL_H
