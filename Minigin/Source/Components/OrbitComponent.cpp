#include "OrbitComponent.h"

#include <numbers>
#include "glm/trigonometric.hpp"

#include "GameObject.h"
#include "SceneManager.h"

using namespace mk;

OrbitComponent::OrbitComponent(float orbitRadius, float rotationSpeed)
	: m_OrbitRadius{ orbitRadius }
	, m_RotationSpeed{ rotationSpeed }
{
}

void OrbitComponent::FixedUpdate()
{
	constexpr float fullRot{ 2.f * std::numbers::pi_v<float> };

	m_Angle += m_RotationSpeed * Time().fixedDeltaTime;
	if (m_Angle > fullRot)
		m_Angle -= fullRot;

	const glm::vec3 offset{ glm::cos(m_Angle) * m_OrbitRadius, glm::sin(m_Angle) * m_OrbitRadius, 0.f };
	GetOwner().SetLocalPosition(offset);
}

void OrbitComponent::SetAngle(float angleDegree)
{
	m_Angle = glm::radians(angleDegree);
}
