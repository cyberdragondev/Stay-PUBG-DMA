#pragma once

#include <Utils/NetConfig/kmboxNet.h>
#include <Utils/NetConfig/HidTable.h>
#include <iostream>

class KmBoxNet
{
public:
    static bool Init(char* IP, char* Port, char* UUID)
    {
        //连接前 PING 一下
        std::string pingCommand = "ping ";
        pingCommand += IP;
        pingCommand += " >nul";
        system(pingCommand.c_str());

        kmNet_init((char*)IP, (char*)Port, (char*)UUID);
        return true;
    }

    static void Clear()
    {
        std::thread([]() {
            std::string pingCommand = "ping ";
            pingCommand += GameData.Config.AimBot.IP;
            pingCommand += " >nul";
            system(pingCommand.c_str());
            //Utils::Log(1, "KMBOXNET Clear Success");
        }).detach();
    }

    static void Close()
    {
        kmNet_reboot();
        //Sleep(5000);
    }

    static void Move(int X, int Y)
    {
        kmNet_mouse_move(X, Y);
    }
};