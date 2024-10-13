#include "string.h"
#include <iostream>
#include <string>
#include <cstdarg>

const char* va(const char* fmt, ...)
{
	static char buffer[1024];

	va_list args;
	va_start(args, fmt);

	std::vsnprintf(buffer, sizeof(buffer), fmt, args);

	va_end(args);

	return buffer;
}