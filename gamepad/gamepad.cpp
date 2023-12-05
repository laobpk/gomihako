#include "gamepad.h"
#include "ui_gamepad.h"

gamepad::gamepad(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gamepad)
{
    ui->setupUi(this);
    joystickthread* thread = new (std::nothrow)joystickthread();
    connect(thread,&joystickthread::sig_joystickex,this,&gamepad::slot_joystick);
    thread->start();

    QTimer* timer = new QTimer(nullptr);
    connect(timer,&QTimer::timeout,this,&gamepad::flush_disp);
    timer->start(10);
}

gamepad::~gamepad()
{
    delete ui;
}

void gamepad::slot_joystick(XINPUT_STATE joyinfo)
{
    _joyinfo = joyinfo;
}

void gamepad::flush_disp()
{
#if 0
//#if (WINVER >= 0x0400)
//typedef struct joyinfoex_tag {
//    DWORD dwSize;                /* size of structure */
//    DWORD dwFlags;               /* flags to indicate what to return */
//    DWORD dwXpos;                /* x position */
//    DWORD dwYpos;                /* y position */
//    DWORD dwZpos;                /* z position */
//    DWORD dwRpos;                /* rudder/4th axis position */
//    DWORD dwUpos;                /* 5th axis position */
//    DWORD dwVpos;                /* 6th axis position */
//    DWORD dwButtons;             /* button states */
//    DWORD dwButtonNumber;        /* current button number pressed */
//    DWORD dwPOV;                 /* point of view state */
//    DWORD dwReserved1;           /* reserved for communication between winmm & driver */
//    DWORD dwReserved2;           /* reserved for future expansion */
//} JOYINFOEX, *PJOYINFOEX, NEAR *NPJOYINFOEX, FAR *LPJOYINFOEX;
//#endif
//    unsigned long xpos = _joyinfo.dwXpos; //l stick h 0x0-0x7fff-0xffff
//    unsigned long ypos = _joyinfo.dwYpos; //l stick v 0x0-0x7fff-0xffff
//    unsigned long rpos = _joyinfo.dwRpos; //r stick v 0x0-0x7fff-0xffff
//    unsigned long upos = _joyinfo.dwUpos; //r stick h 0x0-0x7fff-0xffff
//    unsigned long buttons = _joyinfo.dwButtons;
//    unsigned long pov = _joyinfo.dwPOV; //direction button
    ui->textEdit->append(QString("xpos : %1 ; ypos : %2 ; zpos : %3 ;"
                                 " rpos : %4 ; upos : %5 ; vpos : %6 ;"
                                 " dwButtons : %7 ; dwButtonNumber : %8 ;"
                                 " dwPOV : %9 ; dwReserved1 : %10 ;"
                                 " dwReserved2 : %11 ;")
                         .arg(_joyinfo.dwXpos, 9, 16, QChar('0'))
                         .arg(_joyinfo.dwYpos, 9, 16, QChar('0'))
                         .arg(_joyinfo.dwZpos, 9, 16, QChar('0'))
                         .arg(_joyinfo.dwRpos, 9, 16, QChar('0'))
                         .arg(_joyinfo.dwUpos, 9, 16, QChar('0'))
                         .arg(_joyinfo.dwVpos, 9, 16, QChar('0'))
                         .arg(_joyinfo.dwButtons, 9, 16, QChar('0'))
                         .arg(_joyinfo.dwButtonNumber, 9, 16, QChar('0'))
                         .arg(_joyinfo.dwPOV, 9, 16, QChar('0'))
                         .arg(_joyinfo.dwReserved1, 9, 16, QChar('0'))
                         .arg(_joyinfo.dwReserved2, 9, 16, QChar('0')));
#else
//! typedef struct _XINPUT_STATE
//! {
//!     DWORD                               dwPacketNumber;
//!     XINPUT_GAMEPAD                      Gamepad;
//! } XINPUT_STATE, *PXINPUT_STATE;
//! typedef struct _XINPUT_GAMEPAD
//! {
//!     WORD                                wButtons;
//!     BYTE                                bLeftTrigger;
//!     BYTE                                bRightTrigger;
//!     SHORT                               sThumbLX;
//!     SHORT                               sThumbLY;
//!     SHORT                               sThumbRX;
//!     SHORT                               sThumbRY;
//! } XINPUT_GAMEPAD, *PXINPUT_GAMEPAD;
//    ui->textEdit->append(QString("dwpacketnumber : %1 ; lx : %2 ; ly : %3 ; "
//                                 "rx : %4 ; ry : %5 ; lt : %6 ; rt : %7 ; btn : %8 ;")
//                         .arg(_joyinfo.dwPacketNumber)
//                         .arg(_joyinfo.Gamepad.sThumbLX)
//                         .arg(_joyinfo.Gamepad.sThumbLY)
//                         .arg(_joyinfo.Gamepad.sThumbRX)
//                         .arg(_joyinfo.Gamepad.sThumbRY)
//                         .arg(_joyinfo.Gamepad.bLeftTrigger)
//                         .arg(_joyinfo.Gamepad.bRightTrigger)
//                         .arg(_joyinfo.Gamepad.wButtons));
    SHORT sThumbLX = _joyinfo.Gamepad.sThumbLX; //-32768 - 0 - 32767 left 2 right
    SHORT sThumbLY = _joyinfo.Gamepad.sThumbLY; //-32768 - 0 - 32767 down 2 up
    SHORT sThumbRX = _joyinfo.Gamepad.sThumbRX;
    SHORT sThumbRY = _joyinfo.Gamepad.sThumbRY;
    BYTE bLeftTrigger = _joyinfo.Gamepad.bLeftTrigger;
    ui->vs_lt->setValue(bLeftTrigger);
    BYTE bRightTrigger = _joyinfo.Gamepad.bRightTrigger;
    ui->vs_rt->setValue(bRightTrigger);
    WORD wButtons = _joyinfo.Gamepad.wButtons;
    // 获取myWidget对象的子控件，通过objectName查找QPushButton控件

    for (int i = 0; i < sizeof(WORD) * 8; ++i) {
        int mask = 1 << i;  // 位掩码，将1左移i位
        if (wButtons & mask) {
            // 第i位为1
            // 在这里执行相关操作
            QToolButton *button = ui->frame->findChild<QToolButton*>(QString("btn_%1").arg(i));

            if (button) {
                // 控件找到了，可以进行操作
                button->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(38, 255, 118), stop:1 rgb(38, 255, 118));"
                                      "");
            } else {
                // 控件未找到
//                button->setText("");
            }

        } else {
            // 第i位为0
            QToolButton *button = ui->frame->findChild<QToolButton*>(QString("btn_%1").arg(i));
            if (button) {
                button->setStyleSheet("");
            }
        }
    }

    ui->lb_lt_val->setText(QString::number(bLeftTrigger));
    ui->lb_rt_val->setText(QString::number(bRightTrigger));
    ui->lb_ls_val_x->setText(QString::number(sThumbLX));
    ui->lb_ls_val_y->setText(QString::number(sThumbLY));
    ui->lb_rs_val_x->setText(QString::number(sThumbRX));
    ui->lb_rs_val_y->setText(QString::number(sThumbRY));

    ui->leftstick_image->pos = QPoint(sThumbLX,sThumbLY);
    ui->rightstick_image->pos = QPoint(sThumbRX,sThumbRY);
    ui->leftstick_image->update();
    ui->rightstick_image->update();

#endif
}
