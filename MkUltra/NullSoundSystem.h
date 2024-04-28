#pragma once

#include "SoundSystem.h"

namespace mk
{
	class NullSoundSystem : public SoundSystem
	{
	public:
		NullSoundSystem()			= default;
		~NullSoundSystem() override = default;

		NullSoundSystem(const NullSoundSystem& other)					= delete;
		NullSoundSystem(NullSoundSystem&& other) noexcept				= delete;
		NullSoundSystem& operator=(const NullSoundSystem& other)		= delete;
		NullSoundSystem& operator=(NullSoundSystem&& other)	noexcept	= delete;

		void SetDefaultDataPath(const std::string&) override {}
		void Play(const sound_id&, float) override {}
		void Pause(SoundHandle&) override {}
		void Unpause(SoundHandle&) override {}
		void Stop(SoundHandle&) override {}
		void PlayAudio(const sound_id&, SoundHandle&) override {}
		void StopAll() override {}
	};
}