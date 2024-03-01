#include "MovementComponent.h"

#include <windows.h>

#include "GameObject.h"
#include "SceneManager.h"

using namespace mk;

void MovementComponent::FixedUpdate()
{
	const glm::vec3 travelled{ m_Velocity * Time().fixedDeltaTime };
	GetOwner().AddOffset(travelled);
}

void MovementComponent::Update()
{
	//const glm::vec3 travelled{ m_Velocity * Time().deltaTime };
	//GetOwner().AddOffset(travelled);
	OutputDebugString(std::to_string(1 / Time().GetFPS()).c_str());
}

void MovementComponent::SetVelocity(const glm::vec3& velocity)
{
	m_Velocity = velocity;
}

float MovementComponent::GetSpeed() const
{
	return static_cast<float>(m_Velocity.length());
}

float MovementComponent::GetSpeedSqr() const
{
	return m_Velocity.x * m_Velocity.x + m_Velocity.y * m_Velocity.y + m_Velocity.z * m_Velocity.z;
}
