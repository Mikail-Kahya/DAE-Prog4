#pragma once
#include "IState.h"

namespace mk
{
	class Patrolling : public IState
	{
	public:
		Patrolling() = default;
		~Patrolling() override = default;

		Patrolling(const Patrolling& other)					= delete;
		Patrolling(Patrolling&& other) noexcept				= delete;
		Patrolling& operator=(const Patrolling& other)		= delete;
		Patrolling& operator=(Patrolling&& other) noexcept	= delete;

		void Update() override;

		std::unique_ptr<IState> TransitionState() override;

	private:
		float m_Timer{};
	};

	class TargetPlayer : public IState
	{
	public:
		TargetPlayer() = default;
		~TargetPlayer() override = default;

		TargetPlayer(const TargetPlayer& other)					= delete;
		TargetPlayer(TargetPlayer&& other) noexcept				= delete;
		TargetPlayer& operator=(const TargetPlayer& other)		= delete;
		TargetPlayer& operator=(TargetPlayer&& other) noexcept	= delete;

		std::unique_ptr<IState> TransitionState() override;

	private:
	};
}