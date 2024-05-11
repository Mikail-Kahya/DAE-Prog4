#pragma once
#include <vector>

#include "BoxColliderComponent.h"
#include "ISingleton.h"
#include "glm/vec2.hpp"

namespace mk
{
	class PhysicsSystem final : public ISingleton<PhysicsSystem>
	{
		friend class ISingleton<PhysicsSystem>;
	public:
		~PhysicsSystem() override = default;

		PhysicsSystem(const PhysicsSystem& other)					= delete;
		PhysicsSystem(PhysicsSystem&& other) noexcept				= delete;
		PhysicsSystem& operator=(const PhysicsSystem& other)		= delete;
		PhysicsSystem& operator=(PhysicsSystem&& other)	noexcept	= delete;

		void Update();

		void RegisterCollider(BoxColliderComponent* colliderPtr);
		void UnRegisterCollider(BoxColliderComponent* colliderPtr);

	private:
		PhysicsSystem() = default;

		bool IsOverlapping(BoxColliderComponent* a, BoxColliderComponent* b) const;
		CollisionInfo GetCollisionInfo(BoxColliderComponent* a, BoxColliderComponent* b) const;
		void GetVertices(const glm::vec2& position, const glm::vec2& boxExtent, std::vector<glm::vec2>& vertices) const;

		std::vector<BoxColliderComponent*> m_BoxColliders{};
	};
}
