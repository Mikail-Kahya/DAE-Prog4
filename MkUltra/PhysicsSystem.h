#pragma once
#include <map>
#include <vector>

#include "BoxColliderComponent.h"
#include "ISingleton.h"
#include "glm/vec2.hpp"

namespace mk
{
	struct PhysicsInfo
	{
		glm::vec2 position{};
		glm::vec2 boxExtent{};
	};

	class PhysicsSystem final : public ISingleton<PhysicsSystem>
	{
		friend class ISingleton<PhysicsSystem>;
	public:
		~PhysicsSystem() override = default;

		PhysicsSystem(const PhysicsSystem& other)					= delete;
		PhysicsSystem(PhysicsSystem&& other) noexcept				= delete;
		PhysicsSystem& operator=(const PhysicsSystem& other)		= delete;
		PhysicsSystem& operator=(PhysicsSystem&& other)	noexcept	= delete;

#ifdef NDEBUG
		void DrawDebug() const;
#endif

		void Update();

		void RegisterCollider(BoxColliderComponent* colliderPtr);
		void UnRegisterCollider(BoxColliderComponent* colliderPtr);

	private:
		using Collider = std::pair < BoxColliderComponent*, PhysicsInfo>;

		PhysicsSystem() = default;

		void HandleCollision() const;
		void UpdateInformation();

		static PhysicsInfo GetPhysicsInfo(const BoxColliderComponent* colliderPtr);
		static bool IsOverlapping(const PhysicsInfo& a, const PhysicsInfo& b);
		static CollisionInfo GetCollisionInfo(const PhysicsInfo& a, const PhysicsInfo& b);
		static void GetVertices(const glm::vec2& position, const glm::vec2& boxExtent, std::vector<glm::vec2>& vertices);

		std::vector<Collider> m_PhysicsBuffer{};
	};
}
