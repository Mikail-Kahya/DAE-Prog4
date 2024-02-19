#pragma once

struct Time
{
	Time();

	float GetTotalTime();

	float deltaTime{};
	float fixedTime{};

private:
	std::chrono::steady_clock::time_point start{};
};