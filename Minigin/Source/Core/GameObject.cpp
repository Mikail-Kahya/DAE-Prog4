#include <string>
#include <algorithm>

#include "GameObject.h"

using namespace mk;

GameObject::GameObject(const std::string& name)
	: m_Name{ name }
{
}

GameObject::~GameObject() = default;

GameObject::GameObject(GameObject&& other) noexcept
	: m_Name{ std::move(other.m_Name) }
	, m_Transform{ other.m_Transform }
	, m_Components{ std::move(other.m_Components) }
	, m_Destroy{ other.m_Destroy }
{
	other.m_Components.clear();
}

GameObject& GameObject::operator=(GameObject&& other) noexcept
{
	m_Name = other.m_Name;
	m_Transform = other.m_Transform;
	m_Components = std::move(other.m_Components);
	m_Destroy = other.m_Destroy;

	other.m_Components.clear();

	return *this;
}

void GameObject::RemoveComponent(const std::unique_ptr<Component>& component)
{
	component->Destroy();
}

void GameObject::Update()
{
	for (const auto& component : m_Components)
		component->Update();
}

void GameObject::FixedUpdate()
{
	for (const auto& component : m_Components)
		component->FixedUpdate();
}

void GameObject::LateUpdate()
{
	for (const auto& component : m_Components)
		component->LateUpdate();

	ComponentCleanup();
}

void GameObject::ComponentCleanup()
{
	// Remove destroy flagged components
	auto eraseIt = std::stable_partition(m_Components.begin(), m_Components.end(), [](const std::unique_ptr<Component>& component)
		{
			return !component->DestroyFlagged();
		});

	m_Components.erase(eraseIt, m_Components.end());

	// Move components and flush buffer
	m_Components.insert(m_Components.end(),
		std::make_move_iterator(m_ComponentBuffer.begin()),
		std::make_move_iterator(m_ComponentBuffer.end()));
	m_ComponentBuffer.clear();
}

void GameObject::Destroy()
{
	m_Destroy = true;
}

void GameObject::ClearDestroy()
{
	m_Destroy = false;
}

bool GameObject::DestroyFlagged() const
{
	return m_Destroy;
}

const Transform& GameObject::GetTransform() const
{
	return m_Transform;
}

void GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}
