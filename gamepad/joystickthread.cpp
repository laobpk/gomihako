#include "joystickthread.h"
#if 0
joystickthread::joystickthread()
{

}

void joystickthread::run()
{
//    JOYINFO joyinfo;//定义joystick信息结构体
    JOYINFOEX joyinfoex;
    joyinfoex.dwSize = sizeof(JOYINFOEX);
    joyinfoex.dwFlags = JOY_RETURNALL;
    while(1)
    {
        //读取手柄信息
        UINT joyNums;
        joyNums = joyGetNumDevs();
//		printf("当前手柄数量:%d \n",joyNums);
        if (joyNums>=1)
        {
            MMRESULT joyreturn = joyGetPosEx(JOYSTICKID1, &joyinfoex);
            if(joyreturn == JOYERR_NOERROR)
            {
                emit sig_joystickex(joyinfoex);
//                printf("0x%09lu ", joyinfoex.dwXpos);
//                printf("0x%09lu ", joyinfoex.dwYpos);
//                //printf("0x%09X ", joyinfoex.dwZpos);
//                //printf("0x%09X ", joyinfoex.dwPOV);
//                printf("0x%09lX ", joyinfoex.dwButtons);
//                printf("\n");
            }else
            {
                switch(joyreturn)
                {
                case JOYERR_PARMS :
//                    printf("bad parameters\n");
                    break;
                case JOYERR_NOCANDO :
//                    printf("request not completed\n");
                    break;
                case JOYERR_UNPLUGGED :
//                    printf("joystick is unplugged\n");
                    break;
                default:
//                    printf("未知错误\n");
                    break;
                }
            }
        }

        if(kbhit()) break;
        usleep(300);
    }
}
#else

joystickthread::joystickthread()
{

}

void joystickthread::run()
{
    XINPUT_STATE state;
    DWORD controllerIndex = 0; // 假设您想要获取第一个连接的控制器
    ZeroMemory(&state, sizeof(XINPUT_STATE));

    while(1)
    {
        // 获取控制器的当前状态
        /*DWORD result = */XInputGetState(controllerIndex, &state);
        emit sig_joystickex(state);
//        if (result == ERROR_SUCCESS) {
//            // 获取左触发按钮（LT）的值
//            BYTE ltValue = state.Gamepad.bLeftTrigger;

//            // 获取右触发按钮（RT）的值
//            BYTE rtValue = state.Gamepad.bRightTrigger;

//            // 现在，您可以根据ltValue 和 rtValue 的值来判断 LT 和 RT 的按下程度
//            if (ltValue > 0) {
//                // LT 被按下
//            }

//            if (rtValue > 0) {
//                // RT 被按下
//            }
//        }
        usleep(300);
    }
}

#endif
