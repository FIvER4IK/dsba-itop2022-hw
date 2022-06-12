#ifndef GENREFILTERPROXYMODEL_H
#define GENREFILTERPROXYMODEL_H
#include <QSortFilterProxyModel>
#include <QDate>

class GenreFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit GenreFilterProxyModel(QObject *parent = nullptr);
    void dramaStateChanged();
    void dateSort(const QString& arg1);
    void controlStates(int fl);
    void searchQueryFill(const QString& arg1);
    void search();
    void slider(int sliderState);
    void sliderFilter();
//    bool dramaFilterEnabled() const;

//public slots:
//    void setDramaFilterEnabled(bool enabled);

//signals:
//    void dramaFilterEnabledChanged();

//protected:
//    bool filterAcceptsRow(int sourseRow, const QModelIndex &soureceParent) const;
protected:
    bool lessThan(const QModelIndex& left, const QModelIndex& right) const override;
//    bool lessThan1(const QModelIndex& left, const QModelIndex& right) const;
//    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const  override;

private:
    bool _dramaFilterEnabled;
    bool _comedyFilterEnabled;
    bool _horrorFilterEnabled;
    bool _thrillerFilterEnabled;
    QString _searchQuery;
    int _sortState;
    int _sliderState;
    QString _rxCB;
    QString _rxSl;

};

#endif // GENREFILTERPROXYMODEL_H
