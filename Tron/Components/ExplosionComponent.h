#pragma once
#include "IComponent.h"
#include "IObserver.h"

namespace mk
{
	class ExplosionComponent : public IComponent, public IObserver
	{
	public:
		ExplosionComponent() = default;
		~ExplosionComponent() override = default;

		ExplosionComponent(const ExplosionComponent& other)					= delete;
		ExplosionComponent(ExplosionComponent&& other) noexcept				= delete;
		ExplosionComponent& operator=(const ExplosionComponent& other)		= delete;
		ExplosionComponent& operator=(ExplosionComponent&& other) noexcept	= delete;

		void OnNotify(ISubject* subjectPtr, const Event& event) override;
	};
}
