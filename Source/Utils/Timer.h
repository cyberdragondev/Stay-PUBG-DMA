#pragma once

#include <chrono>
#include <iostream>
#include <string>

class Timer {
public:
	Timer(const std::string& operationName);
	~Timer();
	long long get();

private:
	std::string operationName;
	std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
	bool outputEnabled;
};
