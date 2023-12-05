#ifndef STICKPOS_H
#define STICKPOS_H

#include <QWidget>
#include <QPainter>

class stickpos : public QWidget
{
    Q_OBJECT

public:
    explicit stickpos(QWidget *parent = 0);

    QPoint pos;
    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // STICKPOS_H
