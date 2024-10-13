#ifndef MACHINECODEGENERATOR_H
#define MACHINECODEGENERATOR_H

#include <string>
#include <Windows.h>
#include <iphlpapi.h>
#include <vector>

#pragma comment(lib, "iphlpapi.lib")

class MachineCodeGenerator {
public:
    static std::string GetFirstMacAddress() {
        std::vector<IP_ADAPTER_INFO> adapterInfoList(16);
        DWORD bufferSize = static_cast<DWORD>(adapterInfoList.size() * sizeof(IP_ADAPTER_INFO));

        if (GetAdaptersInfo(adapterInfoList.data(), &bufferSize) == ERROR_BUFFER_OVERFLOW) {
            // 如果缓冲区不够大，重新分配
            adapterInfoList.resize(bufferSize / sizeof(IP_ADAPTER_INFO));
            GetAdaptersInfo(adapterInfoList.data(), &bufferSize);
        }

        // 遍历网络接口并打印MAC地址
        for (const auto& adapterInfo : adapterInfoList) {
            std::string macAddress;
            for (int i = 0; i < adapterInfo.AddressLength; ++i) {
                macAddress += (i == 0 ? "" : ":") + std::to_string(adapterInfo.Address[i]);
            }
            return macAddress;
        }

        return "Error";
    }

    static DWORD GetHddNumber()
    {
        DWORD HddNumber = 0;
        if (GetVolumeInformation("C://", NULL, NULL, &HddNumber, NULL, NULL, NULL, NULL))
        {
            return HddNumber;
        }
        else {
            return 71;
        }
    }

    static std::string GenerateMachineCode() {
        std::string encryption = std::to_string(GetHddNumber() + 0x1339B1A0);
        return encryption;
    }
};

#endif // MACHINECODEGENERATOR_H
