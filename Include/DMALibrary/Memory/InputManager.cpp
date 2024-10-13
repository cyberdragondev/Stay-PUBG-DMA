#include <DMALibrary/pch.h>
#include "InputManager.h"
#include "Registry.h"
#include <DMALibrary/Memory/Memory.h>
#include <Utils/Utils.h>

QWORD c_keys::GetWin32ksgdModuleBase()
{
    return VMMDLL_ProcessGetModuleBaseU(mem.vHandle, 4, (LPSTR)"WIN32KSGD.SYS");
}

DWORD c_keys::FindCsrssPid()
{
    PVMMDLL_PROCESS_INFORMATION winlogonProcess = nullptr;
    std::vector< PVMMDLL_PROCESS_INFORMATION> csrssList;

    DWORD cProcessInformation;
    PVMMDLL_PROCESS_INFORMATION pProcessInformationEntry, pProcessInformationAll = NULL;
    bool result = VMMDLL_ProcessGetInformationAll(mem.vHandle, &pProcessInformationAll, &cProcessInformation);
    if (result)
    {
        // winlogon.exe
        for (int i = 0; i < cProcessInformation; i++) {
            pProcessInformationEntry = &pProcessInformationAll[i];
            if (strcmp(pProcessInformationEntry->szName, "winlogon.exe") == 0)
            {
                winlogonProcess = pProcessInformationEntry;
            }
            else if (strcmp(pProcessInformationEntry->szName, "csrss.exe") == 0)
            {
                csrssList.push_back(pProcessInformationEntry);
            }
        }

        if (winlogonProcess)
        {
            for (const PVMMDLL_PROCESS_INFORMATION& csrss : csrssList)
            {
                if (csrss->dwPPID == winlogonProcess->dwPPID)
                {
                    return csrss->dwPID;
                }
            }
        }
        VMMDLL_MemFree(pProcessInformationAll);
    }
    return 0;
}

DWORD c_keys::GetCsrssPID() {
    static BYTE keyStateBitmap[50];
    DWORD csrssPid = 0;
    DWORD cProcessInformation = 0;

    auto Win32ksgdBaseAddress = GetWin32ksgdModuleBase();
    QWORD** gSessionGlobalSlots = mem.Read<QWORD**>(Win32ksgdBaseAddress + 0x3110, 4);

    for (DWORD session_id = 1; session_id < 100; session_id++)
    {
        QWORD* SessionState = mem.Read<QWORD*>((QWORD)(gSessionGlobalSlots + session_id - 1), 4);
        gafAsyncKeyStateExport = mem.Read<QWORD>((QWORD)SessionState, 4) + 0x3690;
        if (gafAsyncKeyStateExport != 0x3690)
            return 4;
    }

    csrssPid = FindCsrssPid();

    if (csrssPid) {
        uint64_t Win32KBase = NULL;
        PVMMDLL_MAP_MODULEENTRY pModuleMapEntry = NULL;

        PVMMDLL_MAP_EAT pEatMap;
        if (VMMDLL_Map_GetEATU(mem.vHandle, csrssPid, (LPSTR)"win32kbase.sys", &pEatMap))
        {
            for (int i = 0; i < pEatMap->cMap; i++) {
                auto pEatMapEntry = pEatMap->pMap + i;
                std::string functionString(pEatMapEntry->uszFunction);
                size_t start = functionString.find_first_not_of(" ");
                size_t end = functionString.find_last_not_of(" ");
                if (functionString == "gafAsyncKeyState")
                {
                    VMMDLL_MemReadEx(mem.vHandle, csrssPid, pEatMapEntry->vaFunction, (PBYTE)&keyStateBitmap, sizeof(keyStateBitmap), NULL, VMMDLL_FLAG_NOCACHE | VMMDLL_FLAG_NOPAGING_IO);
                    if (!Utils::ValidPtr(keyStateBitmap))
                    {
                        gafAsyncKeyStateExport = pEatMapEntry->vaFunction;
                        return csrssPid;
                    }
                }
            }
            VMMDLL_MemFree(pEatMap);
        }

        std::vector<uint64_t> Offsets = {
            0x24F8A0,
            0x24B8A0,
            0x2498A0,
            0x214320
        };
        gafAsyncKeyStateExport = VMMDLL_ProcessGetProcAddressU(mem.vHandle, csrssPid, (LPSTR)"win32kbase.sys", (LPSTR)"gafAsyncKeyState");
        if (gafAsyncKeyStateExport == 0)
        {
            auto Win32KBase = VMMDLL_ProcessGetModuleBaseU(mem.vHandle, csrssPid, (LPSTR)"win32kbase.sys");
            for (auto Offset : Offsets)
            {
                VMMDLL_MemReadEx(mem.vHandle, csrssPid, Win32KBase + Offset, (PBYTE)&keyStateBitmap, sizeof(keyStateBitmap), NULL, VMMDLL_FLAG_NOCACHE | VMMDLL_FLAG_NOPAGING_IO);
                if (keyStateBitmap[0x24] == '\x2')
                {
                    gafAsyncKeyStateExport = Win32KBase + Offset;
                    break;
                }
            }
        }
        if (gafAsyncKeyStateExport)
        {
            VMMDLL_MemReadEx(mem.vHandle, csrssPid, gafAsyncKeyStateExport, (PBYTE)&keyStateBitmap, sizeof(keyStateBitmap), NULL, VMMDLL_FLAG_NOCACHE | VMMDLL_FLAG_NOPAGING_IO);
            if (keyStateBitmap[0x24] == '\x2')
            {
                return csrssPid;
            }
        }
    }

    return 0;
};

bool c_keys::InitKeyboard()
{
	//std::string win = registry.QueryValue("HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\CurrentBuild", e_registry_type::sz);
	//int Winver = 0;
	//if (!win.empty())
	//	Winver = std::stoi(win);
	//else
	//	return false;

	this->win_logon_pid = mem.GetPidFromName("winlogon.exe");

    auto pids = mem.GetPidListFromName("csrss.exe");
    for (size_t i = 0; i < pids.size(); i++)
    {
        auto pid = pids[i];
        uintptr_t tmp = VMMDLL_ProcessGetModuleBaseU(mem.vHandle, pid, (LPSTR)"win32ksgd.sys");
        uintptr_t g_session_global_slots = tmp + 0x3110;
        uintptr_t user_session_state = mem.Read<uintptr_t>(mem.Read<uintptr_t>(mem.Read<uintptr_t>(g_session_global_slots, pid), pid), pid);

        gafAsyncKeyStateExport = user_session_state + 0x3690;
        if (gafAsyncKeyStateExport > 0x7FFFFFFFFFFF)
            break;
    }
    if (gafAsyncKeyStateExport > 0x7FFFFFFFFFFF)
        return true;

    PVMMDLL_MAP_EAT eat_map = NULL;
    PVMMDLL_MAP_EATENTRY eat_map_entry;
    bool result = VMMDLL_Map_GetEATU(mem.vHandle, mem.GetPidFromName("winlogon.exe") | VMMDLL_PID_PROCESS_WITH_KERNELMEMORY, (LPSTR)"win32kbase.sys", &eat_map);
    if (!result)
        return false;

    if (eat_map->dwVersion != VMMDLL_MAP_EAT_VERSION)
    {
        VMMDLL_MemFree(eat_map);
        eat_map_entry = NULL;
        return false;
    }

    for (int i = 0; i < eat_map->cMap; i++)
    {
        eat_map_entry = eat_map->pMap + i;
        if (strcmp(eat_map_entry->uszFunction, "gafAsyncKeyState") == 0)
        {
            gafAsyncKeyStateExport = eat_map_entry->vaFunction;

            break;
        }
    }

    VMMDLL_MemFree(eat_map);
    eat_map = NULL;
    if (gafAsyncKeyStateExport > 0x7FFFFFFFFFFF)
        return true;

    if (GetCsrssPID()) return true;

    return false;
}

void c_keys::UpdateKeys()
{
	auto prev_key_state_bitmap = key_state_bitmap;
	VMMDLL_MemReadEx(mem.vHandle, this->win_logon_pid | VMMDLL_PID_PROCESS_WITH_KERNELMEMORY, gafAsyncKeyStateExport, (PBYTE)&key_state_bitmap, 64, NULL, VMMDLL_FLAG_NOCACHE);
	for (auto vk = 0u; vk < 256; ++vk) {
		if ((key_state_bitmap[(vk * 2 / 8)] & 1 << vk % 4 * 2) &&
			!(prev_key_state_bitmap[(vk * 2 / 8)] & 1 << vk % 4 * 2))
			key_state_recent_bitmap[vk / 8] |= 1 << vk % 8;
	}
}

bool c_keys::IsKeyDown(std::uint8_t const vk)
{
	return key_state_bitmap[(vk * 2 / 8)] & 1 << vk % 4 * 2;
}

bool c_keys::WasKeyPressed(std::uint8_t const vk) {
	bool const result = key_state_recent_bitmap[vk / 8] & 1 << vk % 8;
	key_state_recent_bitmap[vk / 8] &= ~(1 << vk % 8);
	return result;
}
