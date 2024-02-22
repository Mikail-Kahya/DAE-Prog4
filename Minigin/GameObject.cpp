#include <string>
#include <algorithm>

#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

using namespace dae;

GameObject::GameObject(const std::string& name)
	: m_Name{ name }
{
}

GameObject::~GameObject() = default;

GameObject::GameObject(const GameObject& other)
	: m_Name{ other.m_Name }
	, m_Transform{ other.m_Transform }
	, m_TexturePtr{ other.m_TexturePtr }
	, m_Destroy{ other.m_Destroy }
{
	for (const auto& component : other.m_Components)
		m_Components.emplace_back(std::unique_ptr<Component>(component->Clone()));
}

GameObject::GameObject(GameObject&& other) noexcept
	: m_Name{ std::move(other.m_Name) }
	, m_Transform{ other.m_Transform }
	, m_TexturePtr{ other.m_TexturePtr }
	, m_Components{ std::move(other.m_Components) }
	, m_Destroy{ other.m_Destroy }
{
	other.m_TexturePtr = nullptr;
	other.m_Components.clear();
}

GameObject& GameObject::operator=(const GameObject& other)
{
	m_Name = other.m_Name;
	m_Transform = other.m_Transform;
	m_TexturePtr = other.m_TexturePtr;
	m_Destroy = other.m_Destroy;

	for (const auto& component : other.m_Components)
		m_Components.emplace_back(std::unique_ptr<Component>(component->Clone()));

	return *this;
}

GameObject& GameObject::operator=(GameObject&& other) noexcept
{
	m_Name = other.m_Name;
	m_Transform = other.m_Transform;
	m_TexturePtr = other.m_TexturePtr;
	m_Components = std::move(other.m_Components);
	m_Destroy = other.m_Destroy;

	other.m_TexturePtr = nullptr;
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
}

void GameObject::Render() const
{
	const auto& pos = m_Transform.GetPosition();
	Renderer::GetInstance().RenderTexture(*m_TexturePtr, pos.x, pos.y);
}

void GameObject::ComponentCleanup()
{
	auto eraseIt = std::stable_partition(m_Components.begin(), m_Components.end(), [](const std::unique_ptr<Component>& component)
		{
			return !component->DestroyFlagged();
		});

	m_Components.erase(eraseIt, m_Components.end());
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

void GameObject::SetTexture(const std::string& filename)
{
	m_TexturePtr = ResourceManager::GetInstance().LoadTexture(filename);
}

void GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}