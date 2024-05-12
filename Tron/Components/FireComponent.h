#pragma once
#include "IComponent.h"

namespace mk
{
	class FireComponent : public IComponent
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
