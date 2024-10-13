#pragma once
#include <winsock2.h>
#include <windows.h>

namespace Overlay
{
	int Init();
	void DrawOverlayHandler();
	void Run();
};