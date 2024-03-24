#pragma once
#include "Component.h"
#include "Observer.h"

namespace mk
{
	class HealthComponent : public Component, public Observer, public Subject
	{
	public:
		HealthComponent(int maxHealth, int startHealth);
		~HealthComponent() override = default;

		HealthComponent(const HealthComponent& other)					= delete;
		HealthComponent(HealthComponent&& other) noexcept				= delete;
		HealthComponent& operator=(const HealthComponent& other)		= delete;
		HealthComponent& operator=(HealthComponent&& other)	noexcept	= delete;

		void Start() override;
		void OnNotify(Subject* subjectPtr, const Event& event) override;

		bool IsDead() const;

	private:
		void Hit();
		void Reset();

		const int m_MaxHealth{};
		int m_Health{};
	};
}
