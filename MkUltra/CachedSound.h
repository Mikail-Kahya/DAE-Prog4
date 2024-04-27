#pragma once
#include <chrono>

namespace mk
{
	class CachedSound
	{
	public:
		CachedSound() = default;
		~CachedSound() = default;

		CachedSound(const CachedSound& other)					= default;
		CachedSound(CachedSound&& other) noexcept				= default;
		CachedSound& operator=(const CachedSound& other)		= default;
		CachedSound& operator=(CachedSound&& other)	noexcept	= default;

		void GetSound();
		bool ShouldDestroy() const;

	private:
		void LoadSound();

		static constexpr float CACHE_TIME{ 10.f };

		std::chrono::steady_clock::time_point m_LastUsedTime;
	};
}
