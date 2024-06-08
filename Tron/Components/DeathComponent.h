#pragma once
#include "IComponent.h"
#include "IObserver.h"

namespace mk
{
	class DeathComponent : public IComponent, public IObserver
	{
	public:
		DeathComponent() = default;
		~DeathComponent() override = default;

		DeathComponent(const DeathComponent& other)					= delete;
		DeathComponent(DeathComponent&& other) noexcept				= delete;
		DeathComponent& operator=(const DeathComponent& other)		= delete;
		DeathComponent& operator=(DeathComponent&& other) noexcept	= delete;

		void OnNotify(ISubject* subjectPtr, IEvent* event) override;

	private:
	};
}
