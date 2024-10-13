#pragma once

class Auth
{
public:
    static bool ServeInternetInit()
    {
    }

    static void Init()
    {
        GameData.Config.Window.IsLogin = true;
    }
};