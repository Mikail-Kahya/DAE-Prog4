#include "OrbitComponent.h"

#include "GameObject.h"
#include "SceneManager.h"
#include "glm/trigonometric.hpp"

using namespace mk;

OrbitComponent::OrbitComponent(float orbitRadius, float rotationSpeed)
	: m_OrbitRadius{ orbitRadius }
	, m_RotationSpeed{ rotationSpeed }
{
}

void OrbitComponent::Update()
{
	m_Angle += m_RotationSpeed * Time().deltaTime;
	m_Offset = { glm::cos(m_Angle) * m_OrbitRadius, glm::sin(m_Angle) * m_OrbitRadius, 0.f };
	GetOwner().SetLocalPosition(m_Offset);
}

void OrbitComponent::SetAngle(float angleDegree)
{
	m_Angle = glm::radians(angleDegree);
}
