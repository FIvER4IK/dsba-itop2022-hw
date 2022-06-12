#include "genrefilterproxymodel.h"


GenreFilterProxyModel::GenreFilterProxyModel(QObject* parent)
    : QSortFilterProxyModel(parent)
    , _dramaFilterEnabled(false)
    , _comedyFilterEnabled(false)
    , _horrorFilterEnabled(false)
    , _thrillerFilterEnabled(false)
{
    setDynamicSortFilter(true);
}

//bool GenreFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
//{
//    QModelIndex cbIndex = sourceModel()->index(sourceRow, 1, sourceParent);
//    QModelIndex sliderIndex = sourceModel()->index(sourceRow, 4, sourceParent);

//    QString genre = sourceModel()->data(sliderIndex).toString();
//    QString score = sourceModel()->data(cbIndex).toString();
//    qDebug() << _rxCB;
//    qDebug() << _rxSl;

//    return (genre.contains(_rxCB) && score.contains(_rxSl));
//}

void GenreFilterProxyModel::searchQueryFill(const QString& arg1)
{
    _searchQuery = arg1;
    setFilterRegularExpression(QRegularExpression(_searchQuery));
    setFilterKeyColumn(0);
//    QString rx = arg1;
//    setFilterRegularExpression(QRegularExpression(rx));
//    setFilterKeyColumn(0);
}

void GenreFilterProxyModel::search()
{
    QString rx = _searchQuery;
    setFilterRegularExpression(QRegularExpression(rx));
    setFilterKeyColumn(0);
}

//void GenreFilterProxyModel::dramaStateChanged()
//{
//    setFilterRegularExpression(QRegularExpression("Drama"));

//    setFilterKeyColumn(1);
//}

void GenreFilterProxyModel::controlStates(int fl)
{
    if (fl == 0)
    {
        _dramaFilterEnabled = !_dramaFilterEnabled;
    }
    if (fl == 1)
    {
        _comedyFilterEnabled = !_comedyFilterEnabled;
    }
    if (fl == 2)
    {
        _horrorFilterEnabled = !_horrorFilterEnabled;
    }
    if (fl == 3)
    {
        _thrillerFilterEnabled = !_thrillerFilterEnabled;
    }
    bool isFirstCbx = true;
    QString rx;
    if (_dramaFilterEnabled)
    {
        if (!isFirstCbx)
            rx += '|';
        else
            isFirstCbx = false;

        rx += "(D|d)rama";
    }
    if (_comedyFilterEnabled)
    {
        if (!isFirstCbx)
            rx += '|';
        else
            isFirstCbx = false;
        rx += "(C|c)omedy";
    }
    if (_horrorFilterEnabled)
    {
        if (!isFirstCbx)
            rx += '|';
        else
            isFirstCbx = false;
        rx += "(H|h)orror";
    }
    if (_thrillerFilterEnabled)
    {
        if (!isFirstCbx)
            rx += '|';
        else
            isFirstCbx = false;
        rx += "(T|t)hriller";
    }
    qDebug() << rx;
    _rxCB = rx;
    setFilterRegularExpression(QRegularExpression(rx));
    setFilterKeyColumn(1);
}

void GenreFilterProxyModel::dateSort(const QString& arg1)
{
    QString type = arg1;
    if (type == "premiere")
    {
        _sortState = 0;
        sort(2);
    }
    if (type == "languages")
    {
        _sortState = 1;
        sort(5);
    }
    if (type == "runtime")
    {
        _sortState = 2;
        sort(3);
    }

}

int numOfDate(QString m)
{
    if (m == "January")
        return 1;
    if (m == "Fabruary")
        return 2;
    if (m == "Martch")
        return 3;
    if (m == "April")
        return 4;
    if (m == "May")
        return 5;
    if (m == "June")
        return 6;
    if (m == "July")
        return 7;
    if (m == "August")
        return 8;
    if (m == "September")
        return 9;
    if (m == "October")
        return 10;
    if (m == "November")
        return 11;
    if (m == "Desember")
        return 12;
}

bool GenreFilterProxyModel::lessThan(const QModelIndex& left, const QModelIndex& right) const
{
        QVariant leftData = sourceModel()->data(left);
        QVariant rightData = sourceModel()->data(right);
//        qDebug() << leftData;
//        qDebug() << rightData;
        if (_sortState == 0)
        {
            QString lhs = leftData.toString();
            QString rhs = rightData.toString();
            QStringList lhsList = lhs.split(" ");
            QStringList rhsList = rhs.split(" ");
            for (int i = 0; i < lhsList.size(); ++i)
            {
                lhsList[i].remove(',');
            }
            for (int i = 0; i < rhsList.size(); ++i)
            {
                rhsList[i].remove(',');
            }
//            qDebug() << lhsList;
//            qDebug() << rhsList;
                //QDate date = QDate::fromString(lhsList[0] + lhsList[1] + lhsList[2], )

    //            if (lhsList[2].toInt() <= rhsList[2].toInt())
    //                if (numOfDate(lhsList[0]) <= numOfDate(rhsList[0]))
    //                    if (lhsList[1].toInt() <= rhsList[1].toInt())
    //                        return true;
    //            return false;


            if (lhsList[2].toInt() < rhsList[2].toInt())
                return true;
            else if (lhsList[2].toInt() == rhsList[2].toInt())
            {
                if (numOfDate(lhsList[0]) < numOfDate(rhsList[0]))
                    return true;
                else if (numOfDate(lhsList[0]) == numOfDate(rhsList[0]))
                {
                    if (lhsList[1].toInt() < rhsList[1].toInt())
                        return true;
                }
            }
            return false;
        }
        if (_sortState == 1)
        {
            QString lhs = leftData.toString();
            QString rhs = rightData.toString();
//            qDebug() << lhs;
//            qDebug() << rhs;
            return (lhs < rhs);
        }

        if (_sortState == 2)
        {
            QString lhs = leftData.toString();
            QString rhs = rightData.toString();
            return (lhs.toInt() < rhs.toInt());
        }

//            qDebug() << lhsList[2].toInt();
//            qDebug() << rhsList[2].toInt();
//            qDebug() << (lhsList[2] < rhsList[2]);

//            return lhsList[2] < rhsList[2];
        QString lhs = leftData.toString();
        QString rhs = rightData.toString();
        return lhs.toDouble() < rhs.toDouble();
}

void GenreFilterProxyModel::slider(int sliderState)
{
    _sliderState = sliderState;
    sliderFilter();
}

void GenreFilterProxyModel::sliderFilter()
{
    QString rx;
    int lowerBound = 20;
    if (_sliderState > 20)
        lowerBound = _sliderState;

    for(int i = lowerBound; i < 100; ++i)
    {
        QString i2 = QString::number(i);
        QString score = i2[0] + '.' + i2[1];
        rx += score;
        rx += '|';
    }
    rx += "NoNiNrOw";
    _rxSl = rx;
    setFilterRegularExpression(QRegularExpression(rx));
    setFilterKeyColumn(4);
}
//bool GenreFilterProxyModel::lessThan(const QModelIndex& left, const QModelIndex& right) const
//{
//    QVariant leftData = sourceModel()->data(left);
//    QVariant rightData = sourceModel()->data(right);

////    qDebug() << leftData;
////    qDebug() << rightData;
//    QString lhs = leftData.toString();
//    QString rhs = rightData.toString();
//    QStringList lhsList = lhs.split(" ");
//    QStringList rhsList = lhs.split(" ");
////    for (QString str: lhsList)
////    {
////        str.remove(',');
////    }
////    for (QString str: rhsList)
////    {
////        str.remove(',');
////    }
//    for (int i = 0; i < lhsList.size(); ++i)
//    {
//        lhsList[i].remove(',');
//    }
//    for (int i = 0; i < rhsList.size(); ++i)
//    {
//        rhsList[i].remove(',');
//    }
//    qDebug() << lhsList;
//    qDebug() << rhsList;
//    if (lhsList[2] <= rhsList[2])
//        if (lhsList[1] <= rhsList[1])
//            if (lhsList[0] <= rhsList[0])
//                return false;
//     return true;


////    if (leftData.type() == QVariant::DateTime) {
////        return leftData.toDateTime() < rightData.toDateTime();
////    } else {
////        static const QRegularExpression emailPattern("");

////        QString leftString = leftData.toString();
////        if (left.column() == 1) {
////            const QRegularExpressionMatch match = emailPattern.match(leftString);
////            if (match.hasMatch())
////                leftString = match.captured(0);
////        }
////        QString rightString = rightData.toString();
////        if (right.column() == 1) {
////            const QRegularExpressionMatch match = emailPattern.match(rightString);
////            if (match.hasMatch())
////                rightString = match.captured(0);
////        }

////        return QString::localeAwareCompare(leftString, rightString) < 0;
////    }
//}

//bool GenreFilterProxyModel::dramaFilterEnabled() const
//{
//    return _dramaFilterEnabled;
//}

//void GenreFilterProxyModel::setDramaFilterEnabled(bool enabled)
//{
//    if (_dramaFilterEnabled == enabled)
//        return;

//    _dramaFilterEnabled = enabled;
//    emit dramaFilterEnabledChanged();

//    invalidateFilter();
//}

//bool GenreFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
//{
//    if (!_dramaFilterEnabled)
//        return true;

//    const QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);

//    const QString mediaType = index.data().toString();

//    return (mediaType == "drama");
//}
