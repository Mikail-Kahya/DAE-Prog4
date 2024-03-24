#pragma once
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
		blockDynamic
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

		void CheckCollision(BoxColliderComponent* other);

		CollisionType GetCollision() const;
		void SetCollision(CollisionType type);
		const glm::vec3& GetBoxExtent() const;
		void SetExtent(const glm::vec3& extent);

	private:
		bool CanOverlap() const;
		bool IsOverlapping(BoxColliderComponent* other) const;

		CollisionType m_CollisionType{ CollisionType::overlapAll };
		glm::vec3 m_Extent{30.f, 30.f, 30.f};
	};
}
