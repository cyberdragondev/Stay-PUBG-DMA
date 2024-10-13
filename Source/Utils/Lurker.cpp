#pragma once
#include "Lurker.h"
#include <iostream>
#include <windows.h>
#include <string>
#include "COM.h"
#include <string>
#include <algorithm>

_com LurkerMyserial;

bool Lurker::Init(int com) {
    bool isOpen = LurkerMyserial.open(com, 57600);
    return isOpen;
};

void Lurker::Move(int x, int y) {
    x = (x > 127) ? 127 : (x < -127) ? -127 : x;
    y = (y > 127) ? 127 : (y < -127) ? -127 : y;

    char hexX[3];
    char hexY[3];
    sprintf(hexX, "%02X", (x >= 0) ? x : 256 + x);
    sprintf(hexY, "%02X", (y >= 0) ? y : 256 + y);

    char hex[100];
    sprintf(hex, "57AB0200%s%s00", hexX, hexY);
    LurkerMyserial.writeHex(hex);
};

void Lurker::Close() {
    LurkerMyserial.close();
};
