#pragma once
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#include <codecvt>

#include <windows.h>
#include <iostream>
#include <string>
#include <ShlObj.h>
#include <ctime>
#include <sstream>
#include <regex>
#include <fstream>
#include <iomanip>
#include <setupapi.h>
#include <initguid.h>
#include <devguid.h>
#include <imgui/imgui.h>

#define U8(_S)    (const char*)u8##_S
#define COLOR_RED     "\033[31m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_RESET   "\033[0m"
#define COLOR_LYELLOW "\033[1;33m"
#define COLOR_LGREEN  "\033[1;32m"
#define COLOR_LBLUE   "\033[1;34m"

namespace Utils
{
    inline ImVec4 FloatToImColor(const float Color[4]) {
        return ImVec4(Color[0], Color[1], Color[2], Color[3]);
    }

    inline bool IsLobby(const std::string& mapName) {
        bool IsLobby = (mapName.find("fail") != std::string::npos || mapName.find("None") != std::string::npos || mapName.find("TslLobby") != std::string::npos || mapName.find("Tsl") != std::string::npos);
        if (IsLobby) return IsLobby;
        return mapName.find("Main") == std::string::npos;
    }

    inline bool Contains(std::vector<std::string> vec, std::string str) {
        for (std::string s : vec) {
            if (s == str)
                return true;
        }
        return false;
    }

    inline std::string ReplaceAll(std::string str, const std::string& from, const std::string& to) {
        size_t start_pos = 0;
        while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
            str.replace(start_pos, from.length(), to);
            start_pos += to.length();  // Handles case where 'to' is a substring of 'from'
        }
        return str;
    }

    inline uint32_t ReverseBytes(uint32_t value) {
        return ((value & 0x000000FF) << 24) |
            ((value & 0x0000FF00) << 8) |
            ((value & 0x00FF0000) >> 8) |
            ((value & 0xFF000000) >> 24);
    }

    inline ULONG64 CalcRelative(ULONG64 current)
    {
        return current + *(int32_t*)(current) + 4;
    }

    inline std::string RemoveBracketsAndTrim(const std::string& input) {
        size_t leftBracketPos = input.find('[');
        size_t rightBracketPos = input.find(']');

        if (leftBracketPos != std::string::npos && rightBracketPos != std::string::npos && rightBracketPos > leftBracketPos) {
            std::string result = input.substr(rightBracketPos + 1);
            size_t firstNonSpace = result.find_first_not_of(" ");
            size_t lastNonSpace = result.find_last_not_of(" ");

            if (firstNonSpace != std::string::npos && lastNonSpace != std::string::npos) {
                result = result.substr(firstNonSpace, lastNonSpace - firstNonSpace + 1);
            }
            else {
                result.clear();
            }

            return result;
        }
        else {
            return input;
        }
    }

    inline std::string ExtractSubstring(const std::string& source, const std::string& pattern) {
        if (source == "")
        {
            return "";
        }
        std::regex re(pattern);
        std::smatch match;

        if (std::regex_search(source, match, re) && match.size() > 1) {
            return match.str(1);
        }
        return "";
    }

    inline bool IsPointInScreen(float x, float y, float screenWidth, float screenHeight) {
        return x >= 0 && x <= screenWidth && y >= 0 && y <= screenHeight;
    }

    inline std::vector<std::string> GetCOMPorts() {
        std::vector<std::string> comPorts;

        HDEVINFO hDevInfo;
        SP_DEVINFO_DATA DeviceInfoData;

        hDevInfo = SetupDiGetClassDevs(&GUID_DEVCLASS_PORTS, NULL, NULL, DIGCF_PRESENT);
        if (hDevInfo == INVALID_HANDLE_VALUE) {
            std::cerr << "Failed to get device information set for the COM ports." << std::endl;
            return comPorts;
        }

        DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
        for (DWORD i = 0; SetupDiEnumDeviceInfo(hDevInfo, i, &DeviceInfoData); i++) {
            char friendlyName[256];
            DWORD size = sizeof(friendlyName);

            if (SetupDiGetDeviceRegistryPropertyA(hDevInfo, &DeviceInfoData, SPDRP_FRIENDLYNAME,
                NULL, (PBYTE)friendlyName, size, &size)) {
                comPorts.push_back(friendlyName);
            }
        }

        SetupDiDestroyDeviceInfoList(hDevInfo);
        return comPorts;
    }

    inline float CalculateDistance(float x1, float y1, float x2, float y2) {
        float dx = x2 - x1;
        float dy = y2 - y1;
        return std::sqrt(dx * dx + dy * dy);
    }

    inline void Trim(std::string& s) {
        // Trim from the left
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
            return !std::isspace(ch);
            }));

        // Trim from the right
        s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
            return !std::isspace(ch);
            }).base(), s.end());
    }
    inline bool ValidPtr(uint64_t Ptr)
    {
        return (bool)(Ptr < 0x1000000 || Ptr > 0x7FFFFFF00000 || Ptr % sizeof(uint64_t));
    }

    inline bool ValidPtr(PVOID Ptr)
    {
        auto v1 = (ULONG64)Ptr;

        return (bool)(v1 < 0x1000000 || v1 > 0x7FFFFFF00000 || v1 % sizeof(uint64_t));
    }

    inline std::string ReadConfigFile(const std::string& filename) {
        std::ifstream file(filename);
        std::string content;

        if (!file) {
            return "";
        }

        std::string line;
        while (std::getline(file, line)) {
            content += line + '\n';
        }

        return content;
    }

    inline void WriteConfigFile(const std::string& filename, const std::string& content) {
        std::ofstream file(filename);

        if (!file) {
            return;
        }

        file << content;
    }

    inline char* UnicodeToAnsi(char* wstr)
    {
        if (!wstr) { return NULL; }
        int strleng = WideCharToMultiByte(CP_ACP, NULL, (LPCWCH)wstr, (int)wcslen((LPCWCH)wstr), NULL, 0, NULL, FALSE);
        char* str = new char[strleng + 1];
        WideCharToMultiByte(CP_ACP, NULL, (LPCWCH)wstr, (int)wcslen((LPCWCH)wstr), str, strleng, NULL, FALSE);
        str[strleng] = '\0';
        return str;
    }

    inline std::wstring StringToWstring(const std::string& str) {
        std::wstring res;
        int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, nullptr, 0);
        if (len <= 0) {
            return res;
        }
        res.resize(len - 1); // 减1去除末尾的 null 终止符
        MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, &res[0], len);
        return res;
    }

    inline std::string WstringToUTF8(const std::wstring& wstr) {
        std::string res;
        int len = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
        if (len <= 0) {
            return res;
        }
        res.resize(len - 1); // 减1去除末尾的 null 终止符
        WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &res[0], len, nullptr, nullptr);
        return res;
    }

    inline std::string FormatMinutes(float minutes) {
        // 计算小时和分钟
        int hours = static_cast<int>(minutes / 60);
        int remainingMinutes = static_cast<int>(minutes) % 60;

        // 使用 stringstream 格式化字符串
        std::stringstream ss;
        ss << std::setw(2) << std::setfill('0') << hours << ":";
        ss << std::setw(2) << std::setfill('0') << remainingMinutes;

        return ss.str();
    }

    inline std::string StringToUTF8(const std::string& str) {
        std::wstring wideStr = StringToWstring(str);
        return WstringToUTF8(wideStr);
    }

    inline std::string getCurrentTime() {
        time_t currentTime;
        struct tm timeinfo;

        // 获取当前时间
        time(&currentTime);

        // 使用localtime_s函数代替localtime
        localtime_s(&timeinfo, &currentTime);

        // 将时间转换为time_t类型
        time_t midnight = mktime(&timeinfo);

        // 将时间转换为字符串格式
        char timeStr[9];
        strftime(timeStr, sizeof(timeStr), "%T", &timeinfo);

        return timeStr;
    }

    inline void Log(const int& type, const char* format, ...) {
        std::ostringstream oss;

        //oss << COLOR_LYELLOW << "[" << getCurrentTime() << "]";

        if (type == 1) {
            oss << COLOR_LGREEN << "[+] ";
        }
        else if (type == 2) {
            oss << COLOR_RED << "[X] ";
        }
        else {
            oss << COLOR_LYELLOW << "[-] ";
        }

        va_list args;
        va_start(args, format);
        char buffer[256];
        std::vsnprintf(buffer, sizeof(buffer), format, args);

        va_end(args);

        oss << buffer;
        oss << COLOR_RESET;

        std::cout << oss.str() << std::endl;
    }
}