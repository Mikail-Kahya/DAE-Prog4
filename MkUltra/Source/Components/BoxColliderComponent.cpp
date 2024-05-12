#include "BoxColliderComponent.h"

#include <iostream>

#include "GameObject.h"
#include "Geometry.h"
#include "PhysicsSystem.h"

using namespace mk;

BoxColliderComponent::~BoxColliderComponent()
{
	PhysicsSystem::GetInstance().UnRegisterCollider(this);
}

void BoxColliderComponent::Start()
{
	IComponent::Start();
	PhysicsSystem::GetInstance().RegisterCollider(this);
}

void BoxColliderComponent::Collide(const CollisionInfo& info)
{
	CollisionType type = info.hitCompPtr->GetOwner()->IsStatic() ? m_CollisionSettings.collisionStatic : m_CollisionSettings.collisionDynamic;
	
	switch (type)
	{
	case CollisionType::block:
		HandleBlock(info);
		break;
	case CollisionType::overlap:
		if (!GetOwner()->IsStatic())
			HandleOverlap(info);
		break;
	}
}

bool BoxColliderComponent::IsIgnoring(GameObject* objectPtr) const noexcept
{
	return m_IgnoreObjects.contains(objectPtr);
}

void BoxColliderComponent::Ignore(GameObject* colliderPtr) noexcept
{
	m_IgnoreObjects.insert(colliderPtr);
}

void BoxColliderComponent::StopIgnoring(GameObject* colliderPtr) noexcept
{
	if (m_IgnoreObjects.contains(colliderPtr))
		m_IgnoreObjects.erase(colliderPtr);
}

CollisionSettings BoxColliderComponent::GetCollision() const noexcept
{
	return m_CollisionSettings;
}

const glm::vec2& BoxColliderComponent::GetBoxExtent() const noexcept
{
	return m_Extent;
}

void BoxColliderComponent::SetCollision(CollisionSettings settings) noexcept
{
	auto clampCollision = [](CollisionType type) -> CollisionType
		{
			constexpr int lastIdx{ static_cast<int>(CollisionType::ignore) };
			int idx{ static_cast<int>(type) };
			if (idx < 0 || idx > lastIdx)
				idx = lastIdx;
			return static_cast<CollisionType>(idx);
		};

	settings.collisionDynamic = clampCollision(settings.collisionDynamic);
	settings.collisionStatic = clampCollision(settings.collisionStatic);
	m_CollisionSettings = settings;
}

void BoxColliderComponent::SetExtent(const glm::vec2& extent) noexcept
{
	m_Extent = extent;
}

void BoxColliderComponent::HandleOverlap(const CollisionInfo& info)
{
	Event event{ EventType::OBJECT_OVERLAP };
	event.SetData("info", info);
	Notify(event);
}

void BoxColliderComponent::HandleBlock(const CollisionInfo& info)
{
	const glm::vec2 hitCompPos{ info.hitCompPtr->GetOwner()->GetWorldPosition() };
	const glm::vec2 pos{ GetOwner()->GetWorldPosition() };
	glm::vec2 offset{ glm::normalize(pos - hitCompPos) };
	offset.x *= m_Extent.x;
	offset.y *= m_Extent.y;
	
	GetOwner()->SetLocalPosition(info.intersectionPoint + offset);

	Event event{ EventType::OBJECT_BLOCK };
	event.SetData("info", info);
	Notify(event);
}