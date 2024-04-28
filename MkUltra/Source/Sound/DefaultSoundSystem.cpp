#include "DefaultSoundSystem.h"

#include <chrono>
#include <unordered_map>

#include "soloud.h"
#include "soloud_wav.h"

using namespace mk;

class CachedSound final
{
public:
	CachedSound() = default;
	CachedSound(sound_id id) : m_WaveFile{ std::make_unique<SoLoud::Wav>() }
	{
		m_WaveFile->load(id.c_str());
		constexpr float defaultCacheTime{ 10.f };
		m_CacheTime = defaultCacheTime + static_cast<float>(m_WaveFile->getLength());
		SetTime();
	}
	~CachedSound() = default;

	CachedSound(const CachedSound& other) = delete;
	CachedSound(CachedSound&& other) noexcept = default;
	CachedSound& operator=(const CachedSound& other) = delete;
	CachedSound& operator=(CachedSound&& other)	noexcept = default;

	SoLoud::Wav& GetSound()
	{
		SetTime();
		return *m_WaveFile;
	}
	bool ShouldDestroy() const
	{
		using namespace std::chrono;
		const steady_clock::time_point currentTime{ steady_clock::now() };
		const float deltaTime{ duration<float>(currentTime - m_LastUsedTime).count() };
		return m_CacheTime < deltaTime;
	}

private:
	void SetTime() { m_LastUsedTime = std::chrono::steady_clock::now(); }

	std::chrono::steady_clock::time_point m_LastUsedTime;
	std::unique_ptr<SoLoud::Wav> m_WaveFile{};
	float m_CacheTime{};

};

class DefaultSoundSystem::SoloudImpl final
{
public:
	SoloudImpl() { m_Souloud.init(); }
	~SoloudImpl() { m_Souloud.deinit(); }

	void SetDefaultDataPath(const std::string& dataPath) { m_DefaultDataPath = dataPath; }
	void Update();
	uint32_t Play(sound_id id, float volume);
	void SetPause(uint32_t handle, bool pause) { m_Souloud.setPause(handle, pause); }

	void Stop(uint32_t handle) { m_Souloud.stop(handle); }
	void StopAll() { m_Souloud.stopAll(); }

private:
	void Load(sound_id id) { m_CachedSounds[id] = CachedSound{ m_DefaultDataPath + id }; }

	SoLoud::Soloud m_Souloud{};
	std::unordered_map<sound_id, CachedSound> m_CachedSounds{};
	std::string m_DefaultDataPath{};
};

void DefaultSoundSystem::SoloudImpl::Update()
{
	std::erase_if(m_CachedSounds, [](const auto& cachedSound)
		{
			return cachedSound.second.ShouldDestroy();
		});
}

uint32_t DefaultSoundSystem::SoloudImpl::Play(sound_id id, float volume)
{
	if (!m_CachedSounds.contains(id))
		Load(id);
	return m_Souloud.play(m_CachedSounds[id].GetSound(), volume);
}

DefaultSoundSystem::DefaultSoundSystem()
	: SoundSystem()
	, m_Impl{ std::make_unique<SoloudImpl>() }
	, m_Thread()
{
	SetupThread();
}

DefaultSoundSystem::~DefaultSoundSystem()
{
	m_CloseThread = true;
	m_QueueState.notify_all();
}

void DefaultSoundSystem::SetupThread()
{
	m_Thread = std::jthread([this]()
	{
		while (!m_CloseThread)
		{
			// wait
			std::unique_lock<std::mutex> transferLock{ m_QueueMutex };
			m_QueueState.wait(transferLock, [this] { return !m_Events.empty() || m_CloseThread; });

			// move everything to local queue
			std::queue<Event> events = std::move(this->m_Events);

			transferLock.unlock();

			// perform functions of local queue
			while (!events.empty())
			{
				events.back()();
				events.pop();
			}

			m_Impl->Update();
		}
	});
}

void DefaultSoundSystem::Lock()
{
	m_QueueMutex.lock();
}

void DefaultSoundSystem::Unlock()
{
	m_QueueMutex.unlock();
	m_QueueState.notify_all();
}


void DefaultSoundSystem::SetDefaultDataPath(const std::string& dataPath)
{
	m_Impl->SetDefaultDataPath(dataPath);
}

void DefaultSoundSystem::Play(const sound_id& id, float volume)
{
	Lock();
	m_Events.emplace([this, id, volume]() { m_Impl->Play(std::move(id), volume); });
	Unlock();
}

void DefaultSoundSystem::Pause(SoundHandle&)
{
	//Lock();
	//m_Events.emplace([this, &soundHandle] {m_Impl->SetPause(soundHandle.GetHandle(), true); });
	//Unlock();
}

void DefaultSoundSystem::Unpause(SoundHandle&)
{
	//Lock();
	//m_Events.emplace([this, &soundHandle] {m_Impl->SetPause(soundHandle.GetHandle(), false); });
	//Unlock();
}

void DefaultSoundSystem::Stop(SoundHandle&)
{
	//Lock();
	//m_Events.emplace([this, &soundHandle] {m_Impl->Stop(soundHandle.GetHandle()); });
	//Unlock();
}

void DefaultSoundSystem::PlayAudio(const sound_id&, SoundHandle&)
{
	//Lock();

	//std::promise<uint32_t> promise{};
	//handle = { promise.get_future() };
	//m_Promises.push(std::move(promise));

	//m_Events([this, &handle] { m_Promises.pop() m_Impl->(handle.GetHandle()); });
	//Unlock();
}

void DefaultSoundSystem::StopAll()
{
	Lock();
	m_Events.emplace([this]() {m_Impl->StopAll(); });
	Unlock();
}