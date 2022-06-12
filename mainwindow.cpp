#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _storage(new Storage(this))
    , _model(new NetflixModel(_storage ,this))
    , _proxyModel(new GenreFilterProxyModel(this))
{
    ui->setupUi(this);
//    _storage = new Storage(this);
//    _model = new NetflixModel(new NEt,this);
    //ui->tableView->setModel(_storage->getModel());
    _proxyModel->setSourceModel(_model);
//    _proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
//    ui->tableView->setModel(_proxyModel);
    //ui->tableView->verticalHeader();
    //connect(ui->tableView, SIGNAL(stateChanged()), this, SLOT(on_cbx_1_stateChanged(int arg1)));

    ui->tableView->setModel(_proxyModel);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,         // parent, is needed to restrict focus of the dlg
        "Open File",  // caption — is shown in the main title of the dlg
        "",           // start directory
        "Text files (*.csv)");  // mask which is used for
                                                 // filtering files by their
                                                 // extensions

    _model->layoutAboutToBeChanged();
    //_model->layoutAboutToBeChanged();
    _storage->loadFile(fileName);
    _model->layoutChanged();
    //_mtable->layoutChanged();
//    QString fileName = QFileDialog::getOpenFileName(
//            this,      // parent window (current main window)
//            tr("Open Data Storage File"),   // caption
//            "",                            // init dir
//            tr("Tables (*.csv)") // mask
//            //"Text Files (*.txt)" // mask
//    );
//   _storage->loadFile(fileName);
}

//void MainWindow::on_comboBox_currentIndexChanged(int index)
//{

//}


void MainWindow::on_cbx_1_stateChanged(int arg1)
{
//    _proxyModel->setFilterRegularExpression(QRegularExpression("Drama"));

//    _proxyModel->setFilterKeyColumn(1);
    //_proxyModel->controlStates(0);
    _proxyModel->controlStates(0);
}


void MainWindow::on_cbx_2_stateChanged(int arg1)
{
    //_storage->filterComedy();
    _proxyModel->controlStates(1);
}


void MainWindow::on_cbx_3_stateChanged(int arg1)
{
    //_storage->filterHorror();
    _proxyModel->controlStates(2);
}


void MainWindow::on_cbx_4_stateChanged(int arg1)
{
    //_storage->filterThriller(ui->cbx_4->isChecked());
    _proxyModel->controlStates(3);
}


void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    _proxyModel->dateSort(arg1);
}


void MainWindow::on_line_edt_textChanged(const QString &arg1)
{
   _proxyModel->searchQueryFill(arg1);
}


void MainWindow::on_pushButton_clicked()
{
    _proxyModel->search();
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    _proxyModel->slider(value);
}


void MainWindow::on_actionSave_triggered()
{
    //QDataStream stream(device);
    QString fileName = QFileDialog::getSaveFileName(this,
                tr("save file"), "",
                tr("CSV files (*.csv);;All Files (*)"));
        if (!fileName.isEmpty()) {
            QFile file(fileName);
            if (!file.open(QIODevice::WriteOnly)) {
                QMessageBox::critical(this, tr("Cannot open file"), file.errorString());
                qCritical() << file.errorString();
                return;
            } else {
                QTextStream out(&file);
                QModelIndex index;
                QString oneItem;
                for (int i = 0; i < _model->rowCount(); ++i) {
                    for (int j = 0; j < _model->columnCount(); ++j) {
                        oneItem = _model->data(_model->index(i, j)).toString();
                        if (oneItem.contains(',')) //there we should add double quotes if there comma in cell
                        {
                            out << '\"';
                            out << oneItem;
                            out << '\"';
                        }
                        else
                            out << oneItem;
                        if (j != _model->columnCount() - 1)
                            out << ",";
                    }
                    out << "\n";
                }
                file.close();
            }
        }
}


void MainWindow::on_actionDescriprion_triggered()
{
    about *wdg = new about;
    wdg->show();
}

