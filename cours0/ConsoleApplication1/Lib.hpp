#pragma once

#include <chrono>
#include <ctime>

using namespace std;
using namespace std::chrono;
class Lib {

	double getTimeStamp()
	{
		std::chrono::nanoseconds ns = duration_cast<std::chrono::nanoseconds>(system_clock::now().time_since_epoch());
		return ns.count;
	}
};
