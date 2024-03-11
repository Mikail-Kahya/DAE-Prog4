#include "SceneManager.h"

void mk::SceneManager::FixedUpdate()
{
	for (auto& scene : m_Scenes)
		scene->FixedUpdate();
}

void mk::SceneManager::Update()
{
	for(auto& scene : m_Scenes)
		scene->Update();
}

void mk::SceneManager::LateUpdate()
{
	for (auto& scene : m_Scenes)
		scene->LateUpdate();
}

mk::TimeManager& mk::SceneManager::GetTimeManager()
{
	return m_TimeManager;
}

const mk::TimeManager& mk::Time()
{
	return SceneManager::GetInstance().GetTimeManager();
}

mk::Scene& mk::SceneManager::CreateScene(const std::string& name)
{
	m_Scenes.push_back(std::make_unique<Scene>(name));
	return *m_Scenes.back();
}
