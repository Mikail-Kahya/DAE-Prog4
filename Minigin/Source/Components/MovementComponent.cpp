#include "MovementComponent.h"

#include "DebugUtils.h"
#include "GameObject.h"
#include "SceneManager.h"

using namespace mk;

MovementComponent::MovementComponent(float maxLinearSpeed, float maxAngularSpeed, float acceleration, float deceleration)
	: m_MaxLinearSpeed{ maxLinearSpeed }
	, m_MaxAngularSpeed{ maxAngularSpeed }
	, m_Acceleration{ acceleration }
	, m_Deceleration{ deceleration }
{
}

void MovementComponent::FixedUpdate()
{
	const float deltaTime{ Time().fixedDeltaTime };

	const float deltaSpeed{ m_MaxLinearSpeed * deltaTime };
	if (ShouldMove())
		Accelerate(deltaSpeed * m_Acceleration);
	else if (IsMoving())
		Decelerate(deltaSpeed * m_Deceleration);
	else
		return; // Avoid updating position if not moving

	const glm::vec3 travelled{ m_Velocity * deltaTime };
	GetOwner().AddLocalOffset(travelled);
}

void MovementComponent::SetDirection(const glm::vec3& direction)
{
	m_DesiredDirection = glm::normalize(direction);
}

float MovementComponent::GetSpeed() const
{
	return static_cast<float>(m_Velocity.length());
}

float MovementComponent::GetSpeedSqr() const
{
	return m_Velocity.x * m_Velocity.x + m_Velocity.y * m_Velocity.y + m_Velocity.z * m_Velocity.z;
}

void MovementComponent::Accelerate(float acceleration)
{
	if (GetSpeedSqr() > m_MaxLinearSpeed * m_MaxLinearSpeed)
		return;
	m_Velocity += acceleration * m_DesiredDirection;
}

void MovementComponent::Decelerate(float deceleration)
{
	m_Velocity.x = std::max(0.f, m_Velocity.x - deceleration);
	m_Velocity.y = std::max(0.f, m_Velocity.y - deceleration);
	m_Velocity.z = std::max(0.f, m_Velocity.z - deceleration);
}

bool MovementComponent::IsMoving() const
{
	return GetSpeedSqr() > FLT_EPSILON;
}

bool MovementComponent::ShouldMove() const
{
	const float desiredLengthSqr{ m_DesiredDirection.x * m_DesiredDirection.x
			+ m_DesiredDirection.y * m_DesiredDirection.y
			+ m_DesiredDirection.z * m_DesiredDirection.z };
	return desiredLengthSqr > FLT_EPSILON;
}
