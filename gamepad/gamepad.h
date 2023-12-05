#ifndef GAMEPAD_H
#define GAMEPAD_H

#include <QWidget>
#include <QTimer>
#include "joystickthread.h"

namespace Ui {
class gamepad;
}

class gamepad : public QWidget
{
    Q_OBJECT
#if 0
    //A - 0x01 , B - 0x02 , X - 0x04 , Y - 0x08;
    //rb - 0x20 , lb - 0x10 , start - 0x80 , select - 0x40,
    enum enum_buttons{
        A = 0x01,
        B = 0x02,
        X = 0x04,
        Y = 0x08,
        lb = 0x10,
        rb = 0x20,
        select = 0x40,
        start = 0x80,
        lstickdown = 0x100,
        rstickdown = 0x200
    };

    enum enum_pov{
        none = 0xffff,
        up = 0x0000,        //0000 0000 0000 0000
        left = 0x6978,      //0110 1001 0111 1000
        right = 0x2328,     //0010 0011 0010 1000
        down = 0x4650,      //0100 0110 0101 0000
        leftup = 0x7b0c,    //0111 1011 0000 1100
        rightup = 0x1194,   //0001 0001 1001 0100
        rightdown = 0x34bc, //0011 0100 1011 1100
        leftdown = 0x57e4   //0101 0111 1110 0100
    };
#else
    enum enum_buttons{
        up = 0,//0x01,      //1,    //0001
        down,// = 0x02,    //2,    //0010
        left,// = 0x04,    //4,    //0100
        right,// = 0x08,   //8,    //1000
        start,// = 0x10,   //16,   //0001 0000
        select,// = 0x20,  //32,   //0010 0000
        LS,// = 64,
        RS,// = 128,
        LB,// = 256,
        RB,// = 512,
        A = 12,// = 4096,
        B,// = 8192,
        X,// = 16384,
        Y,// = 32768
    };
#endif
public:
    explicit gamepad(QWidget *parent = nullptr);
    ~gamepad();

private:
    Ui::gamepad *ui;

    XINPUT_STATE _joyinfo;

private slots:
    void slot_joystick(XINPUT_STATE joyinfo);
    void flush_disp();
};

#endif // GAMEPAD_H
