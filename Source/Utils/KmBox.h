#pragma once
#include <iostream>
#include <windows.h>
#include <string>

class KmBox
{
public:
    static bool Init(int com);
    static void Move(int x, int y);
    static void Close();
    static void Clear();
};