#pragma once
#include "Component.h"

namespace mk
{
	class OrbitComponent : public Component
	{
	public:
		OrbitComponent(float orbitRadius = 50.f, float rotationSpeed = 5.f);
		~OrbitComponent() override = default;

		OrbitComponent(const OrbitComponent& other)					= delete;
		OrbitComponent(OrbitComponent&& other) noexcept				= delete;
		OrbitComponent& operator=(const OrbitComponent& other)		= delete;
		OrbitComponent& operator=(OrbitComponent&& other) noexcept	= delete;

		void FixedUpdate() override;

		void SetAngle(float angleDegree);

	private:
		float m_OrbitRadius{};
		float m_RotationSpeed{};
		float m_Angle{};
	};
}
