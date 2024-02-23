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
		Scene& CreateScene(const std::string& name);

		void FixedUpdate();
		void Update();
		void LateUpdate();

		const TimeManager& GetTimeManager();

	private:
		friend class Singleton<SceneManager>;
		friend class Minigin;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_scenes;

		TimeManager m_TimeManager{};
	};
}

inline const TimeManager& Time()
{
	return dae::SceneManager::GetInstance().GetTimeManager();
}