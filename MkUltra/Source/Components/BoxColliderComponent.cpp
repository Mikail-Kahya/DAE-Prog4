#include "BoxColliderComponent.h"

#include "GameObject.h"
#include "Geometry.h"
#include "PhysicsSystem.h"

using namespace mk;

BoxColliderComponent::BoxColliderComponent()
{
	PhysicsSystem::GetInstance().RegisterCollider(this);
}

BoxColliderComponent::~BoxColliderComponent()
{
	PhysicsSystem::GetInstance().UnRegisterCollider(this);
}

void BoxColliderComponent::Start()
{
	Component::Start();
	UpdatePrevPos();
}

void BoxColliderComponent::FixedUpdate()
{
	Component::FixedUpdate();
	UpdatePrevPos();
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

glm::vec2 BoxColliderComponent::GetMoveDirection() const
{
	return glm::normalize(GetOwner()->GetWorldPosition() - m_PrevPos);
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

void BoxColliderComponent::UpdatePrevPos()
{
	m_PrevPos = GetOwner()->GetWorldPosition();
}

void BoxColliderComponent::HandleOverlap(const CollisionInfo& info)
{
	Event event{ EventType::OBJECT_OVERLAP };
	event.SetData("info", info);
	Notify(event);
}

void BoxColliderComponent::HandleBlock(const CollisionInfo& info)
{
	//const float distX{ otherPtr->GetBoxExtent().x + GetBoxExtent().x };
	//const float distY{ otherPtr->GetBoxExtent().y + GetBoxExtent().y };
	//const glm::vec2 toOther{ otherPtr->GetOwner()->GetWorldPosition() - GetOwner()->GetWorldPosition() };

	const glm::vec3 projDir = glm::cross(glm::vec3{ info.impactNormal, 0 }, glm::vec3{ 0, 0, 1 });
	const glm::vec2 slideAlongDir{ glm::normalize(glm::vec2 {projDir.x, projDir.y}) };
	const glm::vec2 moveDir{ m_PrevPos - GetOwner()->GetWorldPosition() };
	const float projectedDist{ glm::dot(slideAlongDir, moveDir) };
	GetOwner()->AddLocalOffset(slideAlongDir * projectedDist);

	//glm::vec2 correction{};


	//if (abs(toOther.x) < distX)
	//{
	//	const float difference{ distX - abs(toOther.x) };
	//	correction.x = toOther.x < 0 ? difference : -difference;
	//}
		
	//if (abs(toOther.y) < distY)
	//{
	//	const float difference{ distY - abs(toOther.y) };
	//	correction.y = toOther.y < 0 ? difference : -difference;
	//}

	
}