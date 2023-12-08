#include "Timer.h"
#include <iostream>

Timer::Timer()
{
	mStartPoint = std::chrono::high_resolution_clock::now();
}

Timer::~Timer()
{
	mEndPoint = std::chrono::high_resolution_clock::now();

	auto start = std::chrono::time_point_cast<std::chrono::microseconds>(mStartPoint).time_since_epoch().count();
	auto end = std::chrono::time_point_cast<std::chrono::microseconds>(mEndPoint).time_since_epoch().count();

	auto duration = end - start;
	double ms = duration * 0.001;
	std::cout << duration << "us (" << ms <<"ms)\n";
	if (ms >= 1000)
	{
		int seconds = ms * 0.001;
		std::cout << seconds << " seconds \n";
	}
}


