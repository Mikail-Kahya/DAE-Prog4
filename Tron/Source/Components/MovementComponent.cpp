#include "MovementComponent.h"

#include <glm/glm.hpp>

#include "GameObject.h"
#include "SceneManager.h"

using namespace mk;

MovementComponent::MovementComponent(float maxLinearSpeed, float maxAngularSpeed, float acceleration, float deceleration, bool consumeMovement)
	: m_MaxLinearSpeed{ maxLinearSpeed }
	, m_MaxAngularSpeed{ maxAngularSpeed }
	, m_Acceleration{ acceleration }
	, m_Deceleration{ deceleration }
	, m_ConsumeMovement{ consumeMovement }
{
}

void MovementComponent::Update()
{
	const float deltaTime{ Time().fixedDeltaTime };

	const float deltaSpeed{ m_MaxLinearSpeed * deltaTime };
	if (ShouldMove())
		Accelerate(deltaSpeed * m_Acceleration);
	else
		Decelerate(deltaSpeed * m_Deceleration);

	const glm::vec2 travelled{ m_Velocity * deltaTime };
	GetOwner()->AddLocalOffset(travelled);
	if (m_ConsumeMovement)
		m_DesiredDirection = {};
}

void MovementComponent::SetDirection(const glm::vec2& direction)
{
	m_DesiredDirection = GetLengthSqr(direction) > FLT_EPSILON ? glm::normalize(direction) : glm::vec2{};
}

const glm::vec2& MovementComponent::GetDirection() const
{
	return m_DesiredDirection;
}

float MovementComponent::GetSpeed() const
{
	return glm::length(m_Velocity);
}

float MovementComponent::GetSpeedSqr() const
{
	return GetLengthSqr(m_Velocity);
}

void MovementComponent::Accelerate(float acceleration)
{
	m_Velocity += acceleration * m_DesiredDirection;
	const float speed = std::min(GetSpeed(), m_MaxLinearSpeed);
	m_Velocity = glm::normalize(m_Velocity) * speed;
}

void MovementComponent::Decelerate(float deceleration)
{
	m_Velocity.x = std::max(0.f, m_Velocity.x - deceleration);
	m_Velocity.y = std::max(0.f, m_Velocity.y - deceleration);
}

bool MovementComponent::IsMoving() const
{
	return GetSpeedSqr() > FLT_EPSILON;
}

bool MovementComponent::ShouldMove() const
{
	const float desiredLengthSqr{ m_DesiredDirection.x * m_DesiredDirection.x
			+ m_DesiredDirection.y * m_DesiredDirection.y };
	return desiredLengthSqr > FLT_EPSILON;
}

float MovementComponent::GetLengthSqr(const glm::vec2& vec)
{
	return vec.x * vec.x + vec.y * vec.y;
}
