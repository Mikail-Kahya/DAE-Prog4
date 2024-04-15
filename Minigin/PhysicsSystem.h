#pragma once
#include <vector>

#include "Singleton.h"

namespace mk
{
	class BoxColliderComponent;

	class PhysicsSystem final : public Singleton<PhysicsSystem>
	{
	public:
		PhysicsSystem() = default;
		~PhysicsSystem() override = default;

		PhysicsSystem(const PhysicsSystem& other)					= delete;
		PhysicsSystem(PhysicsSystem&& other) noexcept				= delete;
		PhysicsSystem& operator=(const PhysicsSystem& other)		= delete;
		PhysicsSystem& operator=(PhysicsSystem&& other)	noexcept	= delete;

		void Update();

		void RegisterCollider(BoxColliderComponent* colliderPtr);
		void UnRegisterCollider(BoxColliderComponent* colliderPtr);

	private:
		bool IsOverlapping(BoxColliderComponent* a, BoxColliderComponent* b) const;

		std::vector<BoxColliderComponent*> m_BoxColliders{};
	};
}
