#pragma once

#include <Windows.h>
#include <cstdint>

static auto DecFunction = reinterpret_cast<uint64_t(*)(uint64_t key, uint64_t base)>(0);

class Decrypt
{
public:
	//解密OBJID
	static DWORD CIndex(DWORD value);
	//解密指针
	static uint64_t Xe(uint64_t addr);
	//销毁解密函数
	static void DestroyXe();
};
