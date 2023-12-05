#ifndef JOYSTICKTHREAD_H
#define JOYSTICKTHREAD_H
#if 0
#include <QThread>
#include <QMetaType>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include<Windows.h>
//添加joystick操作api的支持库
#include<MMSystem.h>
//#pragma comment(lib, "Winmm.lib")

class joystickthread : public QThread
{
    Q_OBJECT

signals:
    void sig_joystickex(JOYINFOEX);

public:
    joystickthread();

protected:
    void run();
};
#else
#include <QThread>
#include <QMetaType>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <Xinput.h>
class joystickthread : public QThread
{
    Q_OBJECT

signals:
    void sig_joystickex(XINPUT_STATE);

public:
    joystickthread();

protected:
    void run();
};
#endif
#endif // JOYSTICKTHREAD_H
