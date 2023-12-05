#ifndef GAMEPADDRAW_H
#define GAMEPADDRAW_H

#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QDebug>
#include <QMouseEvent>
#include "joystickthread.h"

class gamepaddraw : public QWidget
{
    Q_OBJECT
public:
    explicit gamepaddraw(QWidget *parent = nullptr);

signals:

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);

private :
    unsigned char v_lt;
    unsigned char v_rt;
    short v_ls_x;
    short v_ls_y;
    short v_rs_x;
    short v_rs_y;
    QMap<int,bool> b_map;

    QPoint _dragPosition;
private slots:
    void slot_joystick(XINPUT_STATE joyinfo);

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
};

#endif // GAMEPADDRAW_H
