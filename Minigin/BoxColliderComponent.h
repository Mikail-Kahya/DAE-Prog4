#pragma once
#include <set>

#include "Component.h"
#include "Observer.h"
#include "glm/vec3.hpp"

namespace mk
{
	enum class CollisionType
	{
		overlapAll,
		overlapDynamic,
		blockAll,
		blockDynamic,
		none
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
		void Ignore(BoxColliderComponent* colliderPtr) noexcept;
		void StopIgnoring(BoxColliderComponent* colliderPtr) noexcept;

		CollisionType GetCollision() const noexcept;
		const glm::vec3& GetBoxExtent() const noexcept;

		void SetCollision(CollisionType type) noexcept;
		void SetExtent(const glm::vec3& extent) noexcept;

	private:
		bool CanOverlap() const;
		bool IsOverlapping(BoxColliderComponent* other) const;

		std::set<BoxColliderComponent*> m_IgnoreColliders{};
		CollisionType m_CollisionType{ CollisionType::overlapAll };
		glm::vec3 m_Extent{30.f, 30.f, 30.f};
	};
}
