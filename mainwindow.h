#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QFileDialog>
#include <QMessageBox>

#include "storage.h"
#include "netflixmodel.h"
#include "genrefilterproxymodel.h"
#include "about.h"
//#include "logo.h";

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    Storage* _storage;
    NetflixModel* _model;
    GenreFilterProxyModel* _proxyModel;

private slots:
    void on_actionOpen_triggered();


//    void on_comboBox_currentIndexChanged(int index);

    void on_cbx_1_stateChanged(int arg1);

    void on_cbx_2_stateChanged(int arg1);

    void on_cbx_3_stateChanged(int arg1);

    void on_cbx_4_stateChanged(int arg1);

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_line_edt_textChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void on_actionSave_triggered();

    void on_actionDescriprion_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
