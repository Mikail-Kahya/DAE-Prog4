#pragma once
#include <functional>
#include <memory>
#include <queue>

#include "SoundSystem.h"

namespace mk
{
	class DefaultSoundSystem final : public SoundSystem
	{
	public:
		DefaultSoundSystem();
		~DefaultSoundSystem() override;

		DefaultSoundSystem(const DefaultSoundSystem& other)					= delete;
		DefaultSoundSystem(DefaultSoundSystem&& other) noexcept				= delete;
		DefaultSoundSystem& operator=(const DefaultSoundSystem& other)		= delete;
		DefaultSoundSystem& operator=(DefaultSoundSystem&& other) noexcept	= delete;

		void SetDefaultDataPath(const std::string& dataPath) override;
		void Play(const sound_id& id, float volume) override;
		void Pause(SoundHandle& soundHandle) override;
		void Unpause(SoundHandle& soundHandle) override;
		void Stop(SoundHandle& soundHandle) override;
		void PlayAudio(const sound_id& id, SoundHandle& handle) override;
		void StopAll() override;

	private:
		void SetupThread();
		void Lock();
		void Unlock();

		using Event = std::function<void()>;
		class SoloudImpl;

		std::queue<Event> m_Events{};
		std::unique_ptr<SoloudImpl> m_Impl;
		std::condition_variable m_QueueState{};
		std::jthread m_Thread;
		std::mutex m_QueueMutex{};
		bool m_CloseThread{ false };
	};
}