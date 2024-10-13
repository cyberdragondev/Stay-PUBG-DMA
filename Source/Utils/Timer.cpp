#include "Timer.h"
#include <iostream>

Timer::Timer(const std::string& operationName) : operationName(operationName), outputEnabled(true) {
	startTime = std::chrono::high_resolution_clock::now();
}

Timer::~Timer() {
	if (outputEnabled) {
		auto endTime = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
		std::cout << "Operation '" << operationName << "' took: " << duration << " milliseconds" << std::endl;
	}
}

long long Timer::get() {
	outputEnabled = false;
	auto endTime = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
}
