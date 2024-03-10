#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"
#include "TimeManager.h"


namespace mk
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		SceneManager() = default;
		Scene& CreateScene(const std::string& name);

		void FixedUpdate();
		void Update();
		void LateUpdate();

		TimeManager& GetTimeManager();

	private:
		std::vector<std::shared_ptr<Scene>> m_scenes;
		TimeManager m_TimeManager{};
	};

	inline const TimeManager& Time()
	{
		return SceneManager::GetInstance().GetTimeManager();
	}
}
