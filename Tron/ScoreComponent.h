#pragma once
#include "Observer.h"
#include "Component.h"

namespace mk
{
	class TextComponent;

	class ScoreComponent : public Component, public Observer, public Subject
	{
	public:
		ScoreComponent() = default;
		~ScoreComponent() override = default;

		ScoreComponent(const ScoreComponent& other)					= delete;
		ScoreComponent(ScoreComponent&& other) noexcept				= delete;
		ScoreComponent& operator=(const ScoreComponent& other)		= delete;
		ScoreComponent& operator=(ScoreComponent&& other) noexcept	= delete;

		void Start() override;

		void OnNotify(Subject* subjectPtr, const Event& event) override;

	private:
		void AddScore(const Event& event);

		int m_Score{};
		TextComponent* m_TextComponentPtr{};
	};
}