#pragma once
#include <functional>
#include <string>
#include <memory>
#include "ISingleton.h"
#include "TimeManager.h"
#include "Scene.h"

namespace mk
{
	// Design for future when loading from files
		// Load scene with file, allow preloading, and hold one current scene 

	class SceneManager final : public ISingleton<SceneManager>
	{
		friend class ISingleton<SceneManager>;
	public:
		
		~SceneManager() override = default;

		SceneManager(const SceneManager& other)					= delete;
		SceneManager(SceneManager&& other) noexcept				= delete;
		SceneManager& operator=(const SceneManager& other)		= delete;
		SceneManager& operator=(SceneManager&& other) noexcept	= delete;

		void LoadScene(const std::string& name, std::function<void(Scene&)> sceneLoader);
		Scene& GetScene() const;

		void FixedUpdate();
		void Update();
		void LateUpdate();

		TimeManager& GetTimeManager();

	private:
		SceneManager() = default;

		std::unique_ptr<Scene> m_Scene{};
		std::unique_ptr<Scene> m_LoadingScreen{};
		std::unique_ptr<Scene> m_LoadedScene{};
		TimeManager m_TimeManager{};
	};

	const TimeManager& Time();
}
