#pragma once
#include "IComponent.h"
#include "IObserver.h"

namespace mk
{
	class BounceComponent : public IComponent, public IObserver
	{
	public:
		BounceComponent() = default;
		~BounceComponent() override = default;

		BounceComponent(const BounceComponent& other)					= delete;
		BounceComponent(BounceComponent&& other) noexcept				= delete;
		BounceComponent& operator=(const BounceComponent& other)		= delete;
		BounceComponent& operator=(BounceComponent&& other) noexcept	= delete;

		void OnNotify(ISubject* subjectPtr, const Event& event) override;
	};
}
