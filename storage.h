#ifndef STORAGE_H
#define STORAGE_H

#include <QObject>
//#include <QStringListModel>
//#include <QTableView>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
//#include "genrefilterproxymodel.h"
//#include <QDate>

struct Film
{
    QString title;
    QString genre;
    QString premiere;
    int runtime;
    float score;
    QString laguage;
    QStringList line;
    void fillData(const QStringList& details);
    QVariant getData(const QModelIndex& index);
};

//enum class Film
//{
//    QString title;
//    QString genre;
//    QString premiere;
//    int runtime;
//    float score;
//    QString laguage;
//    QStringList line;
//    void fillData(const QStringList& details);
//    QVariant getData(const QModelIndex& index);
//};

class Storage : public QObject
{
    Q_OBJECT
public:
    explicit Storage(QObject *parent = nullptr);

public:
    // Opens a file by the given fileName and reads data from it to the ..model..
    bool loadFile(const QString& fileName);
    //bool saveFile(const QString& fileName);
    //void saveFile(const QString& fileName);

    void filterDrama();
    void filterComedy();
    void filterHorror();
    void filterThriller(bool state);
    QString getFileName();

    //QStandardItemModel* getModel() const { return _model; }
    //GenreFilterProxyModel* getProxyModel() const { return _proxyModel; }

protected:
    bool readFile(); ///< read a file actually
    QString _fileName;
    QStringList _header;
    QList<Film> _films;

public:
    int getSize();
    QVariant getCell(const QModelIndex&);
    QStringList getHeaders();


protected:         ///< stores a given filename
    //NetflixModel* _model;   ///< stores a ptr to our model
    //GenreFilterProxyModel* _proxyModel;  ///sorting model

signals:
    void onFileReaded();        ///< sinal is emit when a file with model data is read succesfully.
};

#endif // STORAGE_H
