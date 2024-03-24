#pragma once

namespace mk
{
	class HealthComponent
	{
	public:
		HealthComponent(int maxHealth, int startHealth);
		~HealthComponent() = default;

		HealthComponent(const HealthComponent& other)					= delete;
		HealthComponent(HealthComponent&& other) noexcept				= delete;
		HealthComponent& operator=(const HealthComponent& other)		= delete;
		HealthComponent& operator=(HealthComponent&& other)	noexcept	= delete;

		void Hit();
		bool IsDead() const;

	private:
		const int m_MaxHealth{};
		int m_Health{};
	};
}