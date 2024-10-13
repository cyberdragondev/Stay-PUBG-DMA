#pragma once

#include <Windows.h>
#include <iostream>
#include <ctype.h>
#include <string.h>
#include <fstream>
#include <io.h>
#include <process.h>

//typedef BOOL(WINAPI* EnumerateFunc) (LPCSTR lpFileOrPath, void* pUserData);

namespace AntiCheat
{
    typedef BOOL(WINAPI* EnumerateFunc) (LPCSTR lpFileOrPath, void* pUserData);

    void doFileEnumeration(LPCSTR lpPath, BOOL bRecursion, BOOL bEnumFiles, EnumerateFunc pFunc, void* pUserData)
    {
        static BOOL s_bUserBreak = FALSE;
        try {
            //-------------------------------------------------------------------------  
            if (s_bUserBreak) return;

            int len = strlen(lpPath);
            if (lpPath == NULL || len <= 0) return;

            //NotifySys(NRS_DO_EVENTS, 0,0);  

            char path[MAX_PATH];
            strcpy(path, lpPath);
            if (lpPath[len - 1] != '\\') strcat(path, "\\");
            strcat(path, "*");

            WIN32_FIND_DATAA fd;
            HANDLE hFindFile = FindFirstFileA(path, &fd);
            if (hFindFile == INVALID_HANDLE_VALUE)
            {
                ::FindClose(hFindFile); return;
            }

            char tempPath[MAX_PATH]; BOOL bUserReture = TRUE; BOOL bIsDirectory;

            BOOL bFinish = FALSE;
            while (!bFinish)
            {
                strcpy(tempPath, lpPath);
                if (lpPath[len - 1] != '\\') strcat(tempPath, "\\");
                strcat(tempPath, fd.cFileName);

                bIsDirectory = ((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0);

                //如果是.或..  
                if (bIsDirectory
                    && (strcmp(fd.cFileName, ".") == 0 || strcmp(fd.cFileName, "..") == 0))
                {
                    bFinish = (FindNextFileA(hFindFile, &fd) == FALSE);
                    continue;
                }

                if (pFunc && bEnumFiles != bIsDirectory)
                {
                    bUserReture = pFunc(tempPath, pUserData);
                    if (bUserReture == FALSE)
                    {
                        s_bUserBreak = TRUE; ::FindClose(hFindFile); return;
                    }
                }

                //NotifySys(NRS_DO_EVENTS, 0,0);  

                if (bIsDirectory && bRecursion) //是子目录  
                {
                    doFileEnumeration(tempPath, bRecursion, bEnumFiles, pFunc, pUserData);
                }

                bFinish = (FindNextFileA(hFindFile, &fd) == FALSE);
            }

            ::FindClose(hFindFile);

            //-------------------------------------------------------------------------  
        }
        catch (...) { return; }
    }
    BOOL WINAPI myEnumerateFunc(LPCSTR lpFileOrPath, void* pUserData) {
        //printf("%s\n", lpFileOrPath);
        if (strstr(lpFileOrPath, "OpenArk.exe") != NULL)
        {
            printf("%s\n", lpFileOrPath);
        }
        if (strstr(lpFileOrPath, "xdbg64.ini") != NULL)
        {
            printf("%s\n", lpFileOrPath);
        }
        if (strstr(lpFileOrPath, "x64dbg.dll") != NULL)
        {
            printf("%s\n", lpFileOrPath);
        }
        /*if (strstr(lpFileOrPath, "VMProtect") != NULL)
        {
            printf("%s\n", lpFileOrPath);
        }*/
        if (strstr(lpFileOrPath, "cheatengine-x86_64.exe") != NULL)
        {
            printf("%s\n", lpFileOrPath);
        }
        if (strstr(lpFileOrPath, "CrazyDbg.exe") != NULL)
        {
            printf("%s\n", lpFileOrPath);

        }
        if (strstr(lpFileOrPath, "CrazyDll64.dll") != NULL)
        {
            printf("%s\n", lpFileOrPath);

        }
        if (strstr(lpFileOrPath, "CrazySys.sys") != NULL)
        {
            printf("%s\n", lpFileOrPath);

        }
        if (strstr(lpFileOrPath, "cheatengine-x86_64") != NULL)
        {
            printf("%s\n", lpFileOrPath);

        }
        if (strstr(lpFileOrPath, "lua53-64.dll") != NULL)
        {
            printf("%s\n", lpFileOrPath);

        }
        if (strstr(lpFileOrPath, "ida64.exe") != NULL)
        {
            printf("%s\n", lpFileOrPath);

        }
        if (strstr(lpFileOrPath, "idat64.exe") != NULL)
        {
            printf("%s\n", lpFileOrPath);

        }
        if (strstr(lpFileOrPath, "win64_remote64.exe") != NULL)
        {
            printf("%s\n", lpFileOrPath);

        }
        return TRUE;
    }

    unsigned _stdcall ThreadProc(void* param)
    {
        char X[20];
        strcpy(X, (char*)param);
        doFileEnumeration(X, TRUE, TRUE, myEnumerateFunc, NULL);
        printf("%s OK\n", X);
        return 0;
    }

    void Run()
    {
        char Devstr[20];


        for (char i = 'A'; i <= 'Z'; i++)
        {
            char x[20] = { i,':' };
            UINT Type = GetDriveTypeA(x);
            if (Type == DRIVE_FIXED || Type == DRIVE_REMOVABLE || Type == DRIVE_CDROM)
            {
                sprintf(Devstr, "%s\\", x);
                _beginthreadex(NULL, 0, ThreadProc, Devstr, NULL, NULL);
                Sleep(100);
                //doFileEnumeration(Devstr, TRUE, TRUE, myEnumerateFunc, NULL);
                //printf("%s OK\n", Devstr);
            }

        }
    }
};