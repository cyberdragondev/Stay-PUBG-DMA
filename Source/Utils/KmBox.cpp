#include "COM.h"
#include "KmBox.h"
#include <iostream>
#include <string>
#include <algorithm>
#include "common/Data.h"
#include <thread>

_com myserial;

void Write(int x, int y)
{
    /*int Max = 127;
    x = (x > Max) ? Max : (x < -Max) ? -Max : x;
    y = (y > Max) ? Max : (y < -Max) ? -Max : y;*/

    char buff[1024];
    snprintf(buff, sizeof(buff), "km.move(%d,%d)\r\n", x, y);
    myserial.write(buff);
}

void ReadKmBox()
{
    while (GameData.Config.AimBot.Connected && GameData.Config.AimBot.Controller == 0)
    {
        Sleep(500);
        char buff[1024];
        myserial.read(buff, 100);
        std::cout << buff << std::endl;
    }
}

void SetScreen(int w, int h)
{
    char buff[1024];
    snprintf(buff, sizeof(buff), "km.screen(%d, %d)\r\n", w, h);
    myserial.write(buff);
}

void Delay(int time)
{
    char buff[1024];
    snprintf(buff, sizeof(buff), "km.delay(%d)\r\n", time);
    myserial.write(buff);
}

void SetFreq(int freq)
{
    char buff[1024];
    snprintf(buff, sizeof(buff), "km.freq(%d)\r\n", freq);
    myserial.write(buff);
}

void Reboot()
{
    char buff[1024];
    snprintf(buff, sizeof(buff), "km.reboot()\r\n");
    myserial.write(buff);
}

bool KmBox::Init(int com)
{
    bool isOpen = myserial.open(com, 115200);
    char ctrlC = 0x03;
    char ctrlD = 0x04;
    myserial.write(&ctrlC, 1);
    Sleep(100);
    SetFreq(1000);
    Sleep(100);
    return isOpen;
}

void KmBox::Close()
{
    myserial.close();
}

void KmBox::Move(int x, int y)
{
    Write(x, y);
}

void KmBox::Clear()
{
    char ctrlC = 0x03;
    myserial.write(&ctrlC, 1);
}