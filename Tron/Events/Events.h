#pragma once
#include "IEvent.h"


namespace mk
{
	struct PlayerDamageTakenEvent : public IEvent
	{
		PlayerDamageTakenEvent(int _health) : health{ _health } {}
		virtual ~PlayerDamageTakenEvent()	= default;
		PlayerDamageTakenEvent(const PlayerDamageTakenEvent& other)					= delete;
		PlayerDamageTakenEvent(PlayerDamageTakenEvent&& other) noexcept				= delete;
		PlayerDamageTakenEvent& operator=(const PlayerDamageTakenEvent& other)		= delete;
		PlayerDamageTakenEvent& operator=(PlayerDamageTakenEvent&& other) noexcept	= delete;

		int health{};
	};

	struct PlayerDiedEvent : public IEvent
	{
		PlayerDiedEvent(int _score) : score{ _score } {}
		virtual ~PlayerDiedEvent()	= default;
		PlayerDiedEvent(const PlayerDiedEvent& other)					= delete;
		PlayerDiedEvent(PlayerDiedEvent&& other) noexcept				= delete;
		PlayerDiedEvent& operator=(const PlayerDiedEvent& other)		= delete;
		PlayerDiedEvent& operator=(PlayerDiedEvent&& other) noexcept	= delete;

		int score{};
	};

	struct ScoreChangedEvent : public IEvent
	{
		ScoreChangedEvent(int _score) : score{ _score } {}
		virtual ~ScoreChangedEvent() = default;
		ScoreChangedEvent(const ScoreChangedEvent& other)					= delete;
		ScoreChangedEvent(ScoreChangedEvent&& other) noexcept				= delete;
		ScoreChangedEvent& operator=(const ScoreChangedEvent& other)		= delete;
		ScoreChangedEvent& operator=(ScoreChangedEvent&& other) noexcept	= delete;

		int score{};
	};
}
