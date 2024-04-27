#pragma once
#include <cstdint>

namespace mk
{
	using sound_id = uint8_t;
	class SoundSystem
	{
	public:
		virtual ~SoundSystem() = default;
		virtual void Play(sound_id id, const float volume) = 0;

	private:
		SoundSystem() = default;
		SoundSystem(const SoundSystem& other)					= delete;
		SoundSystem(SoundSystem&& other) noexcept				= delete;
		SoundSystem& operator=(const SoundSystem& other)		= delete;
		SoundSystem& operator=(SoundSystem&& other)	noexcept	= delete;
	};
}
