#pragma once
#include "IComponent.h"
#include "IObserver.h"

namespace mk
{
	struct BlockEvent;
}

namespace mk
{
	class MovementComponent;

	class BounceComponent : public IComponent, public IObserver
	{
	public:
		BounceComponent(int maxNrBounces);
		~BounceComponent() override = default;

		BounceComponent(const BounceComponent& other)					= delete;
		BounceComponent(BounceComponent&& other) noexcept				= delete;
		BounceComponent& operator=(const BounceComponent& other)		= delete;
		BounceComponent& operator=(BounceComponent&& other) noexcept	= delete;

		void Start() override;

		void FixedUpdate() override;

		void OnNotify(ISubject* subjectPtr, IEvent* event) override;

	private:
		void Bounce(BlockEvent* event);

		static constexpr float BOUNCE_IMMUNITY{ 0.05f };

		MovementComponent* m_MoveCompPtr{};
		const int m_MaxNrBounces{};
		int m_NrBounces{};
		float m_Timer{};
	};
}
