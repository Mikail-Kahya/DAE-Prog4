#pragma once
#include <set>

#include "glm/vec2.hpp"

#include "IComponent.h"
#include "IObserver.h"

namespace mk
{
	class BoxColliderComponent;

	enum class CollisionType : uint8_t
	{
		block,
		overlap,
		ignore
	};

	struct CollisionSettings
	{
		CollisionType collisionStatic{ CollisionType::block };
		CollisionType collisionDynamic{ CollisionType::overlap };
	};

	struct CollisionInfo
	{
		glm::vec2 intersectionPoint{};
		glm::vec2 impactNormal{};
		BoxColliderComponent* hitCompPtr{ nullptr };
		float distance{};
	};

	class BoxColliderComponent final : public IComponent, public ISubject
	{
	public:
		BoxColliderComponent() = default;
		~BoxColliderComponent() override;

		BoxColliderComponent(const BoxColliderComponent& other)					= delete;
		BoxColliderComponent(BoxColliderComponent&& other) noexcept				= delete;
		BoxColliderComponent& operator=(const BoxColliderComponent& other)		= delete;
		BoxColliderComponent& operator=(BoxColliderComponent&& other) noexcept	= delete;

		void Start() override;

		void Collide(const CollisionInfo& info);
		bool IsIgnoring(GameObject* objectPtr) const noexcept;
		void Ignore(GameObject* colliderPtr) noexcept;
		void StopIgnoring(GameObject* colliderPtr) noexcept;

		CollisionSettings GetCollision() const noexcept;
		const glm::vec2& GetBoxExtent() const noexcept;

		void SetCollision(CollisionSettings settings) noexcept;
		void SetExtent(const glm::vec2& extent) noexcept;

	private:
		void HandleOverlap(const CollisionInfo& info);
		void HandleBlock(const CollisionInfo& info);

		std::set<GameObject*> m_IgnoreObjects{};
		CollisionSettings m_CollisionSettings{};
		glm::vec2 m_Extent{30.f, 30.f};
	};
}
