#pragma once
#include "Component.h"
#include "Observer.h"

namespace mk
{
	class ExplosionComponent : public Component, public Observer
	{
	public:
		ExplosionComponent() = default;
		~ExplosionComponent() override = default;

		ExplosionComponent(const ExplosionComponent& other)					= delete;
		ExplosionComponent(ExplosionComponent&& other) noexcept				= delete;
		ExplosionComponent& operator=(const ExplosionComponent& other)		= delete;
		ExplosionComponent& operator=(ExplosionComponent&& other) noexcept	= delete;

		void OnNotify(Subject* subjectPtr, const Event& event) override;
	};
}
