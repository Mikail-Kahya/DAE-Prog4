#pragma once
#include <string>
#include <functional>
#include <filesystem>
#include <chrono>

namespace mk
{
	class Minigin final
	{
	public:
		explicit Minigin(const std::filesystem::path& dataPath);
		~Minigin();
		void Run(const std::function<void()>& load);
		void RunOneFrame();

		Minigin(const Minigin& other) = delete;
		Minigin(Minigin&& other) = delete;
		Minigin& operator=(const Minigin& other) = delete;
		Minigin& operator=(Minigin&& other) = delete;

	private:
		bool m_quit{};
		std::chrono::high_resolution_clock::time_point m_LastTime{};

		static constexpr int FPS{ 60 };
		static constexpr float FIXED_TIME_STEP{ 0.02f };

		float m_Lag{};
	};
}