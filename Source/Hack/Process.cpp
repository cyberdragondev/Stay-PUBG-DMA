#include "Process.h"
#include <DMALibrary/Memory/Memory.h>
#include <Utils/Utils.h>
#include <Common/Data.h>
#include <TlHelp32.h>
#include <Psapi.h>

HANDLE Process::Handle = INVALID_HANDLE_VALUE;
uintptr_t Process::ImageBase = 0;
uint32_t Process::ImageSize = 0;
uint32_t Process::ID = 0;
uint8_t* Process::Dump = nullptr;

bool Process::Init(const std::wstring Process_name)
{
	if (Utils::ValidPtr(GameData.GameBase) || Utils::ValidPtr(GameData.UWorld) || Utils::ValidPtr(GameData.ActorArray)) return false;

	IMAGE_DOS_HEADER DosHeader = mem.Read<IMAGE_DOS_HEADER>(GameData.GameBase);
	IMAGE_NT_HEADERS NtHeader = mem.Read<IMAGE_NT_HEADERS>((GameData.GameBase + DosHeader.e_lfanew));
	Utils::Log(1, "DosHeader: %p", DosHeader);
	Utils::Log(1, "NtHeader.e_lfanew: %p", DosHeader.e_lfanew);
	Utils::Log(1, "NtHeader: %p", NtHeader);

	ImageSize = NtHeader.OptionalHeader.SizeOfImage;
	Dump = new uint8_t[Process::ImageSize];

	mem.Read(GameData.GameBase, (void*)(Dump), ImageSize);

	DWORD OldProtect;
	VirtualProtect(Dump, Process::ImageSize, PAGE_EXECUTE_READWRITE, &OldProtect);

	GameData.VirtualProtect = true;

	return true;

	HANDLE snap_shot{ CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0) };
	if (snap_shot == INVALID_HANDLE_VALUE)
		return false;

	PROCESSENTRY32W Process_entry{ .dwSize = sizeof(PROCESSENTRY32W) };

	for (Process32FirstW(snap_shot, &Process_entry); Process32NextW(snap_shot, &Process_entry); )
		if (wcscmp(Process_name.data(), Process_entry.szExeFile) == NULL)
			ID = Process_entry.th32ProcessID;

	CloseHandle(snap_shot);

	if (!ID || !(Handle = OpenProcess(PROCESS_ALL_ACCESS, false, ID)))
		return false;

	DWORD cbneeded;

	if (K32EnumProcessModulesEx(Handle, (HMODULE*)&ImageBase, sizeof(ImageBase), &cbneeded, LIST_MODULES_64BIT))
	{
		IMAGE_DOS_HEADER dos_header = Read<IMAGE_DOS_HEADER>((void*)ImageBase);
		IMAGE_NT_HEADERS nt_header = Read<IMAGE_NT_HEADERS>((void*)(ImageBase + dos_header.e_lfanew));

		Utils::Log(1, "dos_header: %p", dos_header);
		Utils::Log(1, "dos_header.e_lfanew: %p", dos_header.e_lfanew);
		Utils::Log(1, "nt_header: %p", nt_header);

		ImageSize = nt_header.OptionalHeader.SizeOfImage - 0x1000;
		Dump = new uint8_t[Process::ImageSize];

		for (uint32_t p = 0; p < ImageSize; p += 0x1000)
			Read((void*)(ImageBase + p), (void*)(Dump + p), 0x1000);

		DWORD oldProtect;
		VirtualProtect(Dump, Process::ImageSize, PAGE_EXECUTE_READWRITE, &oldProtect);

		return true;
	}

	return false;
}