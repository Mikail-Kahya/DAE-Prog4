#pragma once
#include <future>
#include <string>

namespace mk
{
	struct SoundHandle
	{
		SoundHandle() = default;
		SoundHandle(std::future<uint32_t> _handle) : handle(std::move(_handle)) {}
		~SoundHandle() = default;
		SoundHandle(const SoundHandle& other) = delete;
		SoundHandle(SoundHandle&& other) noexcept : handle{ std::move(other.handle) }{}
		SoundHandle& operator=(const SoundHandle& other) = delete;
		SoundHandle& operator=(SoundHandle&& other) noexcept
		{
			handle = std::move(other.handle);
			return *this;
		}
		uint32_t GetHandle() { return handle.get(); } // INTERNAL ONLY -- Do not use this function
	private:
		std::future<uint32_t> handle{};
	};

	using sound_id = std::string;

	class SoundSystem
	{
	public:
		virtual ~SoundSystem() = default;
		virtual void SetDefaultDataPath(const std::string& dataPath) = 0;

		virtual void Play(const sound_id& id, float volume) = 0;
		virtual void Pause(SoundHandle& soundHandle) = 0;
		virtual void Unpause(SoundHandle& soundHandle) = 0;
		virtual void Stop(SoundHandle& soundHandle) = 0;
		virtual void PlayAudio(const sound_id&, SoundHandle& handle) = 0;
		virtual void StopAll() = 0;

	protected:
		SoundSystem() = default;
		SoundSystem(const SoundSystem& other)					= delete;
		SoundSystem(SoundSystem&& other) noexcept				= delete;
		SoundSystem& operator=(const SoundSystem& other)		= delete;
		SoundSystem& operator=(SoundSystem&& other)	noexcept	= delete;
	};
}
