#pragma once
#include "Component.h"
#include "Observer.h"

namespace mk
{
	class TextComponent;

	class HealthBarComponent : public Component, public Observer
	{
	public:
		HealthBarComponent() = default;
		~HealthBarComponent() override = default;

		HealthBarComponent(const HealthBarComponent& other)					= delete;
		HealthBarComponent(HealthBarComponent&& other) noexcept				= delete;
		HealthBarComponent& operator=(const HealthBarComponent& other)		= delete;
		HealthBarComponent& operator=(HealthBarComponent&& other) noexcept	= delete;

		void Start() override;

		void OnNotify(Subject* subjectPtr, const Event& event) override;

	private:
		TextComponent* m_TextCompPtr{};
	};
}
