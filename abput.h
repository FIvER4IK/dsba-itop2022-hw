#ifndef ABPUT_H
#define ABPUT_H

#include <QWidget>

namespace Ui {
class Abput;
}

class Abput : public QWidget
{
    Q_OBJECT

public:
    explicit Abput(QWidget *parent = nullptr);
    ~Abput();

private:
    Ui::Abput *ui;
};

#endif // ABPUT_H
