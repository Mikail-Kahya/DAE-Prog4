#include "TimeManager.h"

TimeManager::TimeManager()
	: start{ std::chrono::steady_clock::now() }
{
}

float TimeManager::GetTotalTime() const
{
	using namespace std::chrono;
	return duration<float>(high_resolution_clock::now() - start).count();
}
