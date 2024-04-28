#pragma once
#include "SoundSystem.h"

namespace mk
{
	class ServiceLocator final
	{
	public:
		~ServiceLocator() = default;

		ServiceLocator(const ServiceLocator& other)					= delete;
		ServiceLocator(ServiceLocator&& other) noexcept				= delete;
		ServiceLocator& operator=(const ServiceLocator& other)		= delete;
		ServiceLocator& operator=(ServiceLocator&& other) noexcept	= delete;

		template <std::derived_from<SoundSystem> SystemType, typename ...Args>
		static void RegisterSoundSystem(const Args&... args) { s_SoundSystem = std::make_unique<SystemType>(args...); }
		static SoundSystem& GetSoundSystem();

	private:
		ServiceLocator() = default;

		// services
		inline static std::unique_ptr<SoundSystem> s_SoundSystem{};
	};
}
