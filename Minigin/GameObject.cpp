#include <string>
#include <algorithm>

#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::GameObject(const std::string& name)
	: m_Name{ name }
{
}

dae::GameObject::~GameObject() = default;

void dae::GameObject::RemoveComponent(const std::unique_ptr<Component>& component)
{
	component->Destroy();
}

void dae::GameObject::Update()
{
	for (const auto& component : m_Components)
		component->Update();
}

void dae::GameObject::FixedUpdate()
{
	for (const auto& component : m_Components)
		component->FixedUpdate();
}

void dae::GameObject::LateUpdate()
{
	for (const auto& component : m_Components)
		component->LateUpdate();
}

void dae::GameObject::Render() const
{
	const auto& pos = m_transform.GetPosition();
	Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
}

void dae::GameObject::ComponentCleanup()
{
	auto eraseIt = std::stable_partition(m_Components.begin(), m_Components.end(), [](const std::unique_ptr<Component>& component)
		{
			return !component->DestroyFlagged();
		});

	m_Components.erase(eraseIt, m_Components.end());
}

void dae::GameObject::Destroy()
{
	m_Destroy = true;
}

void dae::GameObject::ClearDestroy()
{
	m_Destroy = false;
}

bool dae::GameObject::DestroyFlagged() const
{
	return m_Destroy;
}

void dae::GameObject::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}

