#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"
#include "TimeManager.h"


namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		virtual ~SceneManager() = default;

		SceneManager(const SceneManager& other) = delete;
		SceneManager(SceneManager&& other) = delete;
		SceneManager& operator=(const SceneManager& other) = delete;
		SceneManager& operator=(SceneManager&& other) = delete;

		Scene& CreateScene(const std::string& name);

		void Update();
		void FixedUpdate();
		void LateUpdate();
		void SceneCleanup();
		void Render();

		const TimeManager& GetTimeManager();

	private:
		friend class Singleton<SceneManager>;
		friend class Minigin;
		SceneManager() = default;

		std::vector<std::unique_ptr<Scene>> m_scenes;
		TimeManager m_TimeManager{};
	};
}

inline const TimeManager& Time()
{
	return dae::SceneManager::GetInstance().GetTimeManager();
}