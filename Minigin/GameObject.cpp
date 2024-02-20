#include <string>
#include <algorithm>

#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::RemoveComponent(std::unique_ptr<Component> component)
{
	component->Destroy();
	//m_Components.erase(std::ranges::find(m_Components, component));
}

void dae::GameObject::RemoveComponents()
{
	auto eraseIt = std::stable_partition(m_Components.begin(), m_Components.end(), [](const std::unique_ptr<Component>& component)
	{
			return !component->DestroyFlagged();
	} );

	m_Components.erase(eraseIt, m_Components.end());
}

void dae::GameObject::FixedUpdate(){}

void dae::GameObject::Update(){}

void dae::GameObject::LateUpdate(){}

void dae::GameObject::Render() const
{
	const auto& pos = m_transform.GetPosition();
	Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
}

void dae::GameObject::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}
