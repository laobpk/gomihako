#include "gamepaddraw.h"
#include "qmath.h"

gamepaddraw::gamepaddraw(QWidget *parent)
    : QWidget{parent}
    , v_lt(0)
    , v_rt(0)
    , v_ls_x(0)
    , v_ls_y(0)
    , v_rs_x(0)
    , v_rs_y(0)
{
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);

    resize(500,500);
    for (int i = 0 ; i < 16; i++)
    {
        if (i == 10 || i == 11)
            continue;
        b_map[i] = false;
    }

    joystickthread* thread = new (std::nothrow)joystickthread();
    connect(thread,&joystickthread::sig_joystickex,this,&gamepaddraw::slot_joystick);
    thread->start();
}

QPointF calculatePoint(int centerX, int centerY, int radius, int angle) {
    qreal x = centerX + radius * std::cos((-angle) * M_PI / 180.0);
    qreal y = centerY + radius * std::sin((-angle) * M_PI / 180.0);
    return QPointF(x, y);
}

void gamepaddraw::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    int side = qMin(width(), height());
//! [10]

//! [11]
    QPainter painter(this);
//! [11] //! [12]
    painter.setRenderHint(QPainter::Antialiasing);
//! [12] //! [13]
    painter.translate(width() / 2, height() / 2);
//! [13] //! [14]
    painter.scale(side / 500.0, side / 500.0);

//! gamepad rounding line start

    QPainterPath path;
    QPen boundingpen = QPen(QColor(0,200,200,100));
    boundingpen.setWidth(2);
    painter.setPen(boundingpen);

// top line
    path.moveTo(-(150-250),165-250);
    path.lineTo(150-250,165-250);
// left top arc
    path.arcTo(150-250 - fabs(165-250),0 - fabs(165-250),
               2 * fabs(165-250), 2 * fabs(165-250),
               90,80);

    QPointF startPoint_left_bottom = calculatePoint(150-250 ,390-250,
                                        fabs(30-150), 160);

    //! left side line
    path.lineTo(startPoint_left_bottom);
    //! left side arc
    path.arcTo(150-250 - fabs(30-150), 390-250 - fabs(30-150),
               2 * fabs(30-150),2 * fabs(30-150),
               160, 40);
    //! left bottom path
    path.cubicTo(45 - 250, 450 - 250, 85 - 250, 450 - 250, 100 - 250, 435 - 250);

    QPointF endPoint_left_bottom_arc = calculatePoint(175-250 ,410-250,
                                        fabs(410-365), 90 + 60);
    path.lineTo(endPoint_left_bottom_arc);
    //! left inside arc
    path.arcTo(175 - 250 - fabs(410-365), 410 - 250 - fabs(410 - 365),
                    2 * fabs(410-365),2 * fabs(410-365),
                    150,-60);
    //! bottom line
    path.lineTo(-(175-250),365-250);

// right bottom arc
    path.arcTo(-(175-250) - fabs(410-365), 410 - 250 - fabs(410 - 365),
               2 * fabs(410-365),2 * fabs(410-365),
               90,-60);

    QPointF endPoint_right_bottom = calculatePoint(-(150-250) ,390-250,
                                        fabs(30-150), -20);
    path.lineTo(-(100 - 250), 435 - 250 );
    path.cubicTo(-(85 - 250), 450 - 250, -(45 - 250), 450 - 250, endPoint_right_bottom.x(), endPoint_right_bottom.y());

    path.arcTo(-(150-250) - fabs(30-150), 390-250 - fabs(30-150),
                    2 * fabs(30-150),2 * fabs(30-150),
                    -20 , 40 );
    QPointF endPoint_right_top = calculatePoint(250-150   ,0,
                                      fabs(165-250), 10 );
    path.lineTo(endPoint_right_top);
    path.arcTo(250-150 - fabs(165-250),-fabs(165-250),
               2 * fabs(165-250), 2 * fabs(165-250),
               10,80);

    painter.drawPath(path);
    painter.fillPath(path,QBrush(QColor(245,245,245)));

// abxy circle (355,235) r = 35
    int r_4circle = 40;
    painter.drawEllipse(QPoint(365 - 250, 235 - 250),r_4circle,r_4circle);
    painter.drawEllipse(QPoint(-(365 - 250), 235 - 250),r_4circle,r_4circle);
// rs circle (305,310) r = 35
    QPoint ls_center = QPoint(-(305 - 250), 310 - 250);
    QPoint rs_center = QPoint(305 - 250, 310 - 250);
    painter.drawEllipse(rs_center,r_4circle,r_4circle);
    painter.drawEllipse(ls_center,r_4circle,r_4circle);

//! gamepad rounding line end

//! draw buttons start
// two sticks
    int stick_radius = r_4circle - 10;

    QPen buttonpen = QPen(QColor(0,0,0));
    buttonpen.setWidth(2);
    painter.setPen(buttonpen);

    path.clear();
    QPointF rstickpos = QPointF(v_rs_x/327.67,-v_rs_y/327.67);
    short opacity = 255 - (int) 255 * (sqrt(pow(v_rs_x,2)+pow(v_rs_y,2)) / 32767);
    (opacity < 1) ? (opacity = 1) : opacity;
    (opacity > 255) ? (opacity = 255) : opacity;
    QBrush stickbrush = QBrush(QColor(opacity,opacity,opacity,180));

    path.addEllipse(rs_center + rstickpos/10.0,stick_radius,stick_radius);
    painter.drawPath(path);
    painter.fillPath(path,stickbrush);

    path.clear();
    opacity = 255 - (int) 255 * (sqrt(pow(v_ls_x,2)+pow(v_ls_y,2)) / 32767);
    (opacity < 1) ? (opacity = 1) : opacity;
    (opacity > 255) ? (opacity = 255) : opacity;
    stickbrush = QBrush(QColor(opacity,opacity,opacity,180));

    QPointF lstickpos = QPointF(v_ls_x/327.67,-v_ls_y/327.67);
    path.addEllipse(ls_center + lstickpos/10.0,stick_radius,stick_radius);
    painter.drawPath(path);
    painter.fillPath(path,stickbrush);

// select (210 235) and start

    path.clear();
    path.addEllipse(QPoint(210-250,235-250),10,10);
    painter.drawPath(path);
    if (b_map.value(5))
        painter.fillPath(path,QBrush(QColor(1,1,1,180)));

    path.clear();
    path.addEllipse(QPoint(-(210-250),235-250),10,10);
    painter.drawPath(path);
    if (b_map.value(4))
        painter.fillPath(path,QBrush(QColor(1,1,1,180)));

// directions
    int btn_radius = 25;
    QRect btn_up(-(365 - 250) - btn_radius,235-250 - btn_radius - 5, 2*btn_radius, 2*btn_radius);
//    painter.drawRect(btn_y);
    painter.setBrush(Qt::NoBrush);
    if (b_map.value(0))
        painter.setBrush(QBrush(QColor(1,1,1,180)));
    painter.drawPie(btn_up, 45 * 16, 90 * 16);

    QRect btn_left(-(365 - 250) - btn_radius - 5,235-250 - btn_radius , 2*btn_radius, 2*btn_radius);
//    painter.drawRect(btn_x);
    painter.setBrush(Qt::NoBrush);
    if (b_map.value(2))
        painter.setBrush(QBrush(QColor(1,1,1,180)));
    painter.drawPie(btn_left, 135 * 16, 90 * 16);

    QRect btn_down(-(365 - 250) - btn_radius ,235-250 - btn_radius + 5, 2*btn_radius, 2*btn_radius);
//    painter.drawRect(btn_a);
    painter.setBrush(Qt::NoBrush);
    if (b_map.value(1))
        painter.setBrush(QBrush(QColor(1,1,1,180)));
    painter.drawPie(btn_down, 225 * 16, 90 * 16);

    QRect btn_right(-(365 - 250) - btn_radius + 5,235-250 - btn_radius , 2*btn_radius, 2*btn_radius);
//    painter.drawRect(btn_b);
    painter.setBrush(Qt::NoBrush);
    if (b_map.value(3))
        painter.setBrush(QBrush(QColor(1,1,1,180)));
    painter.drawPie(btn_right, 315 * 16, 90 * 16);

// abxy
    QRect btn_y(365-250 - btn_radius,235-250 - btn_radius - 5, 2*btn_radius, 2*btn_radius);
//    painter.drawRect(btn_y);
    painter.setBrush(Qt::NoBrush);
    if (b_map.value(15))
        painter.setBrush(QBrush(QColor(1,1,1,180)));
    painter.drawPie(btn_y, 45 * 16, 90 * 16);

    QRect btn_x(365-250 - btn_radius - 5,235-250 - btn_radius , 2*btn_radius, 2*btn_radius);
//    painter.drawRect(btn_x);
    painter.setBrush(Qt::NoBrush);
    if (b_map.value(14))
        painter.setBrush(QBrush(QColor(1,1,1,180)));
    painter.drawPie(btn_x, 135 * 16, 90 * 16);

    QRect btn_a(365-250 - btn_radius ,235-250 - btn_radius + 5, 2*btn_radius, 2*btn_radius);
//    painter.drawRect(btn_a);
    painter.setBrush(Qt::NoBrush);
    if (b_map.value(12))
        painter.setBrush(QBrush(QColor(1,1,1,180)));
    painter.drawPie(btn_a, 225 * 16, 90 * 16);

    QRect btn_b(365-250 - btn_radius + 5,235-250 - btn_radius , 2*btn_radius, 2*btn_radius);
//    painter.drawRect(btn_b);
    painter.setBrush(Qt::NoBrush);
    if (b_map.value(13))
        painter.setBrush(QBrush(QColor(1,1,1,180)));
    painter.drawPie(btn_b, 315 * 16, 90 * 16);

// lb (158 142) rb
    path.clear();
    path.addRoundedRect(158-250 - 20,142-250 - 7, 40, 14,7,7);
    painter.drawPath(path);
    if (b_map.value(8))
        painter.fillPath(path,QBrush(QColor(1,1,1,180)));
    else
        painter.fillPath(path,QBrush(QColor(245,245,245)));

    path.clear();
    path.addRoundedRect(-(158-250) - 20,142-250 - 7, 40, 14,7,7);
    painter.drawPath(path);
    if (b_map.value(9))
        painter.fillPath(path,QBrush(QColor(1,1,1,180)));
    else
        painter.fillPath(path,QBrush(QColor(245,245,245)));

// lt rt
    path.clear();
    path.addRoundedRect(158-250 - 15,102-250 - 25, 30, 50, 7, 7);
    painter.drawPath(path);
    painter.fillPath(path,QBrush(QColor(255-v_lt,255-v_lt,255-v_lt,180)));

    path.clear();
    path.addRoundedRect(-(158-250) - 15,102-250 - 25, 30, 50, 7, 7);
    painter.drawPath(path);
    painter.fillPath(path,QBrush(QColor(255-v_rt,255-v_rt,255-v_rt,180)));


//! draw buttons end

}

void gamepaddraw::slot_joystick(XINPUT_STATE joyinfo)
{
    v_lt = joyinfo.Gamepad.bLeftTrigger;
    v_rt = joyinfo.Gamepad.bRightTrigger;
    v_ls_x = joyinfo.Gamepad.sThumbLX;
    v_ls_y = joyinfo.Gamepad.sThumbLY;
    v_rs_x = joyinfo.Gamepad.sThumbRX;
    v_rs_y = joyinfo.Gamepad.sThumbRY;

    WORD wButtons = joyinfo.Gamepad.wButtons;
    for (int i = 0; i < sizeof(WORD) * 8; ++i) {
        int mask = 1 << i;  // 位掩码，将1左移i位
        if (i == 10 || i == 11)
            continue;
        if (wButtons & mask) {
            // 第i位为1
            // 在这里执行相关操作
            b_map[i] = true;
        } else {
            // 第i位为0
            b_map[i] = false;
        }
    }


    this->update();
}

void gamepaddraw::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        _dragPosition = e->globalPos() - this->frameGeometry().topLeft();
    }
}

void gamepaddraw::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons() & Qt::LeftButton)
    {
        if(this->isMaximized())
            return;
        move(e->globalPos() - _dragPosition);
    }
}

