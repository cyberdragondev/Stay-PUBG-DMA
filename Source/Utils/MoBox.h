#pragma once
#include <iostream>
#include <windows.h>

class MoBox
{
public:

    static bool Init(int com);
    static void Move(int x, int y);
    static void Close();
};