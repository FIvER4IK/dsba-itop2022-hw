#ifndef ABOUT_H
#define ABOUT_H

#include <QWidget>

#include "logo.h"

namespace Ui {
class about;
}

class about : public QWidget
{
    Q_OBJECT

public:
    explicit about(QWidget *parent = nullptr);
    ~about();

protected:
    void updateConfigUi();

private:
    Ui::about *ui;
    Logo* _logo;
};

#endif // ABOUT_H
