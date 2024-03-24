#pragma once
#include "Component.h"
#include "glm/vec3.hpp"

namespace mk
{
	class FireComponent : public Component
	{
	public:
		FireComponent(float barrelLength);
		~FireComponent() override = default;

		FireComponent(const FireComponent& other)					= delete;
		FireComponent(FireComponent&& other) noexcept				= delete;
		FireComponent& operator=(const FireComponent& other)		= delete;
		FireComponent& operator=(FireComponent&& other) noexcept	= delete;

		void Fire() const;

	private:
		float m_BarrelLength{};
	};
}
