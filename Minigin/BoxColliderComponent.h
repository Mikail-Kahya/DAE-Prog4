#pragma once
#include <set>

#include "Component.h"
#include "Observer.h"
#include "glm/vec3.hpp"

namespace mk
{
	enum class CollisionType
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

	class BoxColliderComponent : public Component, public Subject
	{
	public:
		BoxColliderComponent();
		~BoxColliderComponent() override;

		BoxColliderComponent(const BoxColliderComponent& other)					= delete;
		BoxColliderComponent(BoxColliderComponent&& other) noexcept				= delete;
		BoxColliderComponent& operator=(const BoxColliderComponent& other)		= delete;
		BoxColliderComponent& operator=(BoxColliderComponent&& other) noexcept	= delete;

		void CheckCollision(BoxColliderComponent* otherPtr);
		void Ignore(GameObject* colliderPtr) noexcept;
		void StopIgnoring(GameObject* colliderPtr) noexcept;

		CollisionSettings GetCollision() const noexcept;
		const glm::vec3& GetBoxExtent() const noexcept;

		void SetCollision(CollisionSettings settings) noexcept;
		void SetExtent(const glm::vec3& extent) noexcept;

	private:
		void HandleOverlap(BoxColliderComponent* otherPtr);
		void HandleBlock(BoxColliderComponent* otherPtr);
		bool IsOverlapping(BoxColliderComponent* other) const;

		std::set<GameObject*> m_IgnoreObjects{};
		CollisionSettings m_CollisionSettings{};
		glm::vec3 m_Extent{30.f, 30.f, 30.f};
	};
}
