#ifndef LOGO_H
#define LOGO_H

#include <QWidget>

class Logo : public QWidget
{
    Q_OBJECT
public:
    explicit Logo(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event);

signals:

};

#endif // LOGO_H
