#pragma once
#include "MoBox.h"
#include <iostream>
#include <windows.h>
#include "common/Data.h"

HMODULE kmdll = nullptr;
typedef void (*SetScreenScale)(int, int);
typedef int (*OpenDevice)(const char*);
typedef void (*EnableAccurateDelay)();
typedef void (*CloseDevice)();
typedef void (*MoveR)(int, int);

OpenDevice MoOpenDevice = nullptr;
SetScreenScale MoSetScreenScale = nullptr;
EnableAccurateDelay MoEnableAccurateDelay = nullptr;
CloseDevice MoCloseDevice = nullptr;
MoveR MoMoveR = nullptr;

bool MoBox::Init(int com) {
    kmdll = LoadLibrary("ddll64.dll");
    if (!kmdll) {
        return false;
    }

    MoOpenDevice = (OpenDevice)GetProcAddress(kmdll, "OpenDevice");
    MoSetScreenScale = (SetScreenScale)GetProcAddress(kmdll, "SetScreenScale");
    MoEnableAccurateDelay = (EnableAccurateDelay)GetProcAddress(kmdll, "EnableAccurateDelay");
    MoCloseDevice = (EnableAccurateDelay)GetProcAddress(kmdll, "Close");
    MoMoveR = (MoveR)GetProcAddress(kmdll, "MoveR");

    if (!MoOpenDevice || !MoSetScreenScale || !MoEnableAccurateDelay || !MoCloseDevice || !MoMoveR) {
        return false;
    }

    char comStr[10];
    snprintf(comStr, sizeof(comStr), "COM%d", com);
    int ret = MoOpenDevice(comStr);
    if (!ret) {
        return false;
    }
    else {
       MoSetScreenScale(GameData.Config.Overlay.ScreenWidth, GameData.Config.Overlay.ScreenHeight);
       MoEnableAccurateDelay();
    }

    return true;
};

void MoBox::Move(int x, int y)
{
    MoMoveR(x, y);
}

void MoBox::Close() {
    MoCloseDevice();
}