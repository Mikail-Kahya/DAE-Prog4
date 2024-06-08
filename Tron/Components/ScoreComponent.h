#pragma once
#include "IObserver.h"
#include "IComponent.h"

namespace mk
{
	struct ObjectDiedEvent;
	class TextComponent;

	class ScoreComponent : public IComponent, public IObserver, public ISubject
	{
	public:
		ScoreComponent() = default;
		~ScoreComponent() override = default;

		ScoreComponent(const ScoreComponent& other)					= delete;
		ScoreComponent(ScoreComponent&& other) noexcept				= delete;
		ScoreComponent& operator=(const ScoreComponent& other)		= delete;
		ScoreComponent& operator=(ScoreComponent&& other) noexcept	= delete;

		void Start() override;

		void OnNotify(ISubject* subjectPtr, IEvent* event) override;

	private:
		void AddScore(const ObjectDiedEvent* event);

		int m_Score{};
		TextComponent* m_TextComponentPtr{};
	};
}
