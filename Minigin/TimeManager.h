#pragma once
#include <chrono>

struct TimeManager
{
	TimeManager();

	float GetTotalTime() const;

	float deltaTime{};
	float fixedDeltaTime{ 0.2f };

private:
	std::chrono::steady_clock::time_point start{};
};
