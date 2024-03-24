#pragma once
#include "Observer.h"
#include "Component.h"

namespace mk
{
	class ScoreComponent : public Component, public Subject
	{
	public:
		ScoreComponent() = default;
		~ScoreComponent() override = default;

		ScoreComponent(const ScoreComponent& other)					= delete;
		ScoreComponent(ScoreComponent&& other) noexcept				= delete;
		ScoreComponent& operator=(const ScoreComponent& other)		= delete;
		ScoreComponent& operator=(ScoreComponent&& other) noexcept	= delete;

	private:
		void AddScore(const Event& event);

		int m_Score{};
	};
}
