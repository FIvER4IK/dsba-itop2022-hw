#include "storage.h"
#include "mainwindow.h"

#include <stdexcept>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QStringList>
#include <QString>
#include <QRegularExpression>
#include <QSortFilterProxyModel>
#include <QButtonGroup>

void Film::fillData(const QStringList& details)
{
    if (details.size() < 6)
        throw std::invalid_argument("invalid desc");
    title = details[0];
    genre = details[1];
    premiere = details[2];
    runtime = details[3].toInt();;
    score = details[4].toDouble();
    laguage = details[5];
    line = details;
}

QVariant Film::getData(const QModelIndex& indx) { return true; }


Storage::Storage(QObject* parent)
    : QObject{parent}
{
    //_model = new NetflixModel(this);
    //_proxyModel->setSourceModel(_model);
    //_proxyModel->setSourceModel(_model);
}

QStringList Storage::getHeaders() { return _header; };
int Storage::getSize() { return _films.size(); }
QVariant Storage::getCell(const QModelIndex& indx)
{
    return _films.at(indx.row()).line.at(indx.column());
};

bool Storage::loadFile(const QString& fileName)
{
    _fileName = fileName;
    //qDebug() << _fileName;

    //readFile(_fileName);
//    if(readFile())
//        emit onFileReaded(/*some potential parameters here*/);
    return readFile();
}

//void Storage::saveFile(const QString& fileName)
//{
//    if(fileName.isEmpty())
//        return;
//    QFile file(fileName);
//    if(!file.open(QIODevice::WriteOnly))
//    {
//        //emit onFileNotRead();
//        return;
//    }
//    QTextStream out(&file);
//    for (int i = 0; i < _model->stringList().size(); ++i)
//        out << _model->stringList().at(i) << Qt::endl << '\n';
//    file.close();
//}

QString Storage::getFileName()
{
    return _fileName;
}

bool Storage::readFile()
{
    QFile file(_fileName);
    if (file.open(QIODevice::ReadOnly))
    {
        size_t lineindex = 0;
        QTextStream in(&file);
        QString fileLine = in.readLine();
        QRegularExpression rx(",(?=([^\"]*\"[^\"]*\")*[^\"]*$)");
        _header = fileLine.split(",", Qt::SkipEmptyParts);
        while (!in.atEnd())
        {
            fileLine = in.readLine();
            QStringList line = fileLine.split(rx);
            for (int i = 0; i < line.size(); ++i)
            {
                line[i].remove("\"");
            }
            Film p;
            p.fillData(line);
            _films.append(p);
            lineindex++;
        }
        file.close();
        return true;
    }
    return false;
}


//bool Storage::readFile()           ///< read a file actually
//{
//    qDebug() << _fileName;

//    if (_fileName.isEmpty())
//        throw std::invalid_argument("File name not set");

//    QFile file(_fileName);

//    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
//        return false;
//    }

//    QModelIndex index;
//    QTextStream table(&file);
//    QString line = table.readLine();
//    QStringList values = line.split(',');

//    //_model->setRowCount(1);
//    _model->setColumnCount(values.size());

//    _model->setHorizontalHeaderLabels(values); // Header

//    int rowCount = 1;
//    while (!table.atEnd()) {
//        _model->setRowCount(rowCount);
//        line = table.readLine();
//        // Scv file have comma symbol as a dilimetr
//        // there is some commas inside double quotse, and should not be dilimetrs
//        // so use QRegularExpression to split by comma but ignore commas inside double quotes
//        QRegularExpression rx(",(?=([^\"]*\"[^\"]*\")*[^\"]*$)");
//        values = line.split(rx);

//        for (int i = 0; i < values.size(); ++i)
//        {
//            values[i].remove("\"");
//        }

//        //values = line.split(',');
//        int colCount = values.size();
//        _model->setColumnCount(colCount);
//        for (int i = 0; i < values.size(); ++i)
//        {
//            index = _model->index(rowCount - 1, i);
//            _model->setData(index, values[i]);
//        }
//        ++rowCount;
//    }
//    file.close();
//    return true;
//}

//void Storage::filterDrama()
//{
//    _proxyModel->setFilterRegularExpression(QRegularExpression("Drama"));

//    _proxyModel->setFilterKeyColumn(1);
//}

//void Storage::filterComedy()
//{
//    _proxyModel->setFilterRegularExpression(QRegularExpression("Comedy"));

//    _proxyModel->setFilterKeyColumn(1);
//}

//void Storage::filterHorror()
//{
//    _proxyModel->setFilterRegularExpression(QRegularExpression("Horror"));

//    _proxyModel->setFilterKeyColumn(1);
//}

//void Storage::filterThriller(bool state)
//{
//    if (state == 1)
//    {
//        _proxyModel->setFilterRegularExpression(QRegularExpression("Thriller"));

//        _proxyModel->setFilterKeyColumn(1);
//    }
//    else
//    {
//        _proxyModel->setFilterRegularExpression(QRegularExpression());

//        _proxyModel->setFilterKeyColumn(1);
//    }
//}

