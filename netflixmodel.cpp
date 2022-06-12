#include "netflixmodel.h"
#include <QFile>

NetflixModel::NetflixModel(Storage* films, QObject* parent)
    : QAbstractTableModel{parent}
    , _films{films}
{

}

int NetflixModel::rowCount(const QModelIndex& parent) const
{
    return _films->getSize();
};
int NetflixModel::columnCount(const QModelIndex& parent) const
{
    return _films->getHeaders().size();
};

QVariant NetflixModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        return _films->getCell(index);
    }
    return QVariant();
};

QVariant NetflixModel::headerData(int section, Qt::Orientation orientation,
                                int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    if (orientation == Qt::Horizontal)
        return _films->getHeaders().at(section);
    return QVariant();
};


//void NetflixModel::fillDataTableFromFile(QString path)
//{
//    QFile inputFile(path);
//    inputFile.open(QFile::ReadOnly | QFile::Text);
//    QTextStream inputStream(&inputFile);

//    QString firstline = inputStream.readLine();
//    for (QString& item : firstline.split(",")) {
//        _headerList.append(item);
//    }

//    while(!inputStream.atEnd())
//    {
//        QString line = inputStream.readLine();

//        QList<QString> dataRow;
//        for (QString& item : line.split(",")) {
//            dataRow.append(item);
//        }
//        dataTable.append(dataRow);
//    }
//    inputFile.close();
//}

//int NetflixModel::rowCount(const QModelIndex &parent) const
//{
//    if (parent.isValid())
//        return 0;

//    return dataTable.size();
//}

//int NetflixModel::columnCount(const QModelIndex &parent) const
//{
//    if (parent.isValid())
//        return 0;

//    if (dataTable.empty())
//    {
//        return 0;
//    }

//    return dataTable[0].size();
//}

//QVariant NetflixModel::headerData(int section, Qt::Orientation orientation, int role) const
//{
//    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
//    {
//        return headerList[section];
//    }
//    return QVariant();
//}

//QVariant NetflixModel::data(const QModelIndex &index, int role) const
//{
//    if (!index.isValid())
//        return QVariant();

//    if (role == Qt::DisplayRole || role == Qt::EditRole)
//    {
//        int row = index.row();
//        int col = index.column();
//        return dataTable[row][col];
//    }
//    return QVariant();
//}

//bool NetflixModel::setData(const QModelIndex &index, const QVariant &value, int role)
//{
//    if (data(index, role) != value) {
//        int row = index.row();
//        int col = index.column();
//        dataTable[row][col] = value.toString();
//        emit dataChanged(index, index, {role});
//        return true;
//    }
//    return false;
//}

//Qt::ItemFlags NetflixModel::flags(const QModelIndex &index) const
//{
//    if (!index.isValid())
//        return Qt::NoItemFlags;

//    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
//}

//void NetflixModel::appendRow(const QList<QString> &row)
//{
//    size_t newRowNumber = rowCount();
//    beginInsertRows(QModelIndex(), newRowNumber, newRowNumber);
//    dataTable.append(row);
//    endInsertRows();
//}
