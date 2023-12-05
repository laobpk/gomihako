#include "stickpos.h"

stickpos::stickpos(QWidget *parent) :
    QWidget(parent),
    pos(QPoint(0,0))
{

}

void stickpos::paintEvent(QPaintEvent *event)
{
    QColor edge(127,127,127);
    QColor stick(50,50,50);

    int side = qMin(width(), height());
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width() / 2, height() / 2);
    painter.scale(side / 150.0, side / 150.0);

    painter.setPen(edge);

    painter.save();
    painter.drawEllipse(-50,-50,100,100);
    painter.restore();
    painter.setPen(Qt::NoPen);
    painter.setBrush(edge);
    painter.save();
    painter.drawEllipse(-2,-2,4,4);
    painter.restore();

    painter.setPen(stick);
    painter.setBrush(stick);
    painter.save();
    QPointF stickpos = QPointF(pos.x()/327.67/2.0,-pos.y()/327.67/2.0);
    painter.drawEllipse(stickpos.x()-2,stickpos.y()-2,4,4);
    painter.drawLine(stickpos.x(), stickpos.y(), 0, 0);
    painter.restore();
}
