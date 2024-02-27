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
	, m_Destroy{ other.m_Destroy }
	, m_LocalTransform{ other.m_LocalTransform }
	, m_WorldTransform{ other.m_WorldTransform }
	, m_PositionIsDirty{ other.m_PositionIsDirty }
	, m_Parent{ other.m_Parent }
	, m_Children{ std::move(other.m_Children) }
	, m_Components{ std::move(other.m_Components) }
	, m_ComponentBuffer{ std::move(other.m_ComponentBuffer) }
	
{
	other.m_Parent = nullptr;
}

GameObject& GameObject::operator=(GameObject&& other) noexcept
{
	m_Name = other.m_Name;
	m_Destroy = other.m_Destroy;
	m_LocalTransform = other.m_LocalTransform;
	m_WorldTransform = other.m_WorldTransform;
	m_PositionIsDirty = other.m_PositionIsDirty;
	m_Parent = other.m_Parent;
	m_Children = std::move(other.m_Children);
	m_Components = std::move(other.m_Components);
	m_ComponentBuffer = std::move(other.m_ComponentBuffer);

	other.m_Parent = nullptr;

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

void GameObject::AddChild(GameObject* child)
{
	m_Children.push_back(child);
}

void GameObject::RemoveChild(GameObject* child)
{
	m_Children.erase(std::ranges::find(m_Children, child));
}

bool GameObject::IsChild(GameObject* child) const
{
	const auto foundChild{ std::ranges::find(m_Children, child) };
	return foundChild != m_Children.cend();
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

const glm::vec3& GameObject::GetWorldPosition()
{
	if (m_PositionIsDirty)
		UpdateWorldPosition();
	return m_WorldTransform.GetPosition();
}

void GameObject::SetPosition(float x, float y)
{
	SetPosition({ x, y, m_LocalTransform.GetPosition().z });
}

void GameObject::SetPosition(float x, float y, float z)
{
	SetPosition({ x, y, z });
}

void GameObject::SetPosition(const glm::vec3& position)
{
	m_LocalTransform.SetPosition(position);
	FlagPositionDirty();
}

void GameObject::UpdateWorldPosition()
{
	if (!m_PositionIsDirty)
		return;

	if (m_Parent == nullptr)
		m_WorldTransform.SetPosition(m_LocalTransform.GetPosition());
	else
		m_WorldTransform.SetPosition(m_Parent->GetWorldPosition() + m_LocalTransform.GetPosition());

	m_PositionIsDirty = false;
}

void GameObject::FlagPositionDirty()
{
	m_PositionIsDirty = true;
}

void GameObject::SetParent(GameObject* parent, bool keepWorldPosition)
{
	if (m_Parent == parent || this == parent || IsChild(parent))
		return;

	if (parent == nullptr)
		SetPosition(GetWorldPosition());
	else
	{
		if (keepWorldPosition)
			SetPosition(m_LocalTransform.GetPosition() - parent->GetWorldPosition());
		FlagPositionDirty();
	}

	if (m_Parent != nullptr)
		m_Parent->RemoveChild(this);
	m_Parent = parent;
	if (m_Parent != nullptr)
		m_Parent->AddChild(this);
}

int GameObject::GetChildCount() const
{
	return static_cast<int>(m_Children.size());
}

GameObject* GameObject::GetChildAt(int index) const
{
	if (index > m_Children.size())
		return nullptr;
	return m_Children[index];
}
