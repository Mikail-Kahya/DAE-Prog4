#include "Scene.h"
#include "GameObject.h"

#include <algorithm>

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}


Scene::~Scene() = default;

GameObject& Scene::CreateGameObject(const std::string& name)
{
	m_objects.emplace_back(GameObject{ name });
	return m_objects.back();
}

void Scene::RemoveDestroyed()
{
	auto eraseIt = std::stable_partition(m_objects.begin(), m_objects.end(), [](const std::unique_ptr<GameObject>& object)
	{
		return !object->DestroyFlagged();
	});

	m_objects.erase(eraseIt, m_objects.end());
}

void Scene::RemoveAll()
{
	m_objects.clear();
}

void Scene::Update()
{
	for(auto& object : m_objects)
		object.Update();
}

void Scene::FixedUpdate()
{
	for (auto& object : m_objects)
	{
		object.FixedUpdate();
	}
}

void Scene::LateUpdate()
{
	for (auto& object : m_objects)
		object.LateUpdate();
}

void Scene::ObjectCleanup()
{
	for (auto& object : m_objects)
		object.ComponentCleanup();
	RemoveDestroyed();
}

void Scene::Render() const
{
	for (const auto& object : m_objects)
	{
		object.Render();
	}
}

