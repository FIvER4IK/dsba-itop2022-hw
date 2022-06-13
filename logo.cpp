#include "logo.h"
#include <QPainter>

Logo::Logo(QWidget *parent)
    : QWidget{parent}
{

}

void Logo::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing, true);

    QRadialGradient radialGrad(QPointF(10, 30), 50);
    radialGrad.setColorAt(0, Qt::GlobalColor::darkMagenta);
    radialGrad.setColorAt(0.5, QColor(100, 53, 203));
    radialGrad.setColorAt(1, Qt::yellow);
    QBrush backBrush(radialGrad);
    painter.setBrush(backBrush);
    painter.drawRect(QRect(0, 0, width() - 1, height() - 1 ));


}
