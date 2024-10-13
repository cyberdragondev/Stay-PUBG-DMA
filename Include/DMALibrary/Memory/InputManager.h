#pragma once
#include "../pch.h"
#include "Registry.h"
#include <array>

class c_keys
{
private:
	uint64_t gafAsyncKeyStateExport = 0;
	uint8_t state_bitmap[64] { };
	uint8_t previous_state_bitmap[256 / 8] { };

	std::array<std::uint8_t, 256 * 2 / 8> key_state_bitmap;
	std::array<std::uint8_t, 256 / 8> key_state_recent_bitmap;

	uint64_t win32kbase = 0;

	int win_logon_pid = 0;

	c_registry registry;

public:
	c_keys() = default;

	~c_keys() = default;

	bool InitKeyboard();
	QWORD GetWin32ksgdModuleBase();
	DWORD FindCsrssPid();
	DWORD GetCsrssPID();

	void UpdateKeys();
	bool IsKeyDown(std::uint8_t const vk);
	bool WasKeyPressed(std::uint8_t const vk);
};
