#pragma once
#include "Component.h"
#include "glm/vec3.hpp"

namespace mk
{
	class FireComponent : public Component
	{
	public:
		FireComponent(const glm::vec3& socketOffset);
		~FireComponent() override = default;

		FireComponent(const FireComponent& other)					= delete;
		FireComponent(FireComponent&& other) noexcept				= delete;
		FireComponent& operator=(const FireComponent& other)		= delete;
		FireComponent& operator=(FireComponent&& other) noexcept	= delete;

		void Fire() const;

	private:
		const glm::vec3 m_SocketOffset{};
	};
}
