#pragma once

#include <windows.h>
#include <string>

#pragma comment(lib, "ntdll.lib")
#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)

extern "C"
{
	NTSTATUS NTAPI NtReadVirtualMemory(HANDLE, PVOID, PVOID, ULONG, PULONG);
}

namespace Process
{
	extern HANDLE Handle;
	extern uintptr_t ImageBase;
	extern uint32_t ImageSize;
	extern uint32_t ID;
	extern uint8_t* Dump;

	bool Init(const std::wstring process_name);

	template <typename T>
	T Read(void* address)
	{
		T buffer{};
		NT_SUCCESS(NtReadVirtualMemory(Handle, (void*)address, &buffer, sizeof(buffer), nullptr));
		return buffer;
	}

	template <typename T>
	T Read(uint64_t address)
	{
		T buffer{};
		NT_SUCCESS(NtReadVirtualMemory(Handle, (void*)address, &buffer, sizeof(buffer), nullptr));
		return buffer;
	}

	template <typename T>
	bool Read(void* address, T buffer, size_t size)
	{
		return NT_SUCCESS(NtReadVirtualMemory(Handle, address, buffer, size, nullptr));
	}
}