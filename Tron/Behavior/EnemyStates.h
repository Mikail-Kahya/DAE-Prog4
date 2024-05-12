#pragma once
#include "GameObjectState.h"

namespace mk
{
	class MovementComponent;
	class SensorComponent;

	class Patrolling : public GameObjectState
	{
	public:
		Patrolling() = default;
		~Patrolling() override = default;

		Patrolling(const Patrolling& other)					= delete;
		Patrolling(Patrolling&& other) noexcept				= delete;
		Patrolling& operator=(const Patrolling& other)		= delete;
		Patrolling& operator=(Patrolling&& other) noexcept	= delete;

		void Start() override;
		void Update() override;

		std::string TransitionState() override;

	private:
		MovementComponent* m_MovementPtr{};
		SensorComponent* m_SensorPtr{};
		float m_Timer{};
	};

	class MoveBackFromWall : public GameObjectState
	{
	public:
		MoveBackFromWall() = default;
		~MoveBackFromWall() override = default;

		MoveBackFromWall(const MoveBackFromWall& other) = delete;
		MoveBackFromWall(MoveBackFromWall&& other) noexcept = delete;
		MoveBackFromWall& operator=(const MoveBackFromWall& other) = delete;
		MoveBackFromWall& operator=(MoveBackFromWall&& other) noexcept = delete;

		void Start() override;

		void Update() override;
		std::string TransitionState() override;

	private:
		MovementComponent* m_MovementPtr{};
		inline static constexpr float m_MoveTime{ 0.5f };
		float m_Timer{};
	};

	class Rotate : public GameObjectState
	{
	public:
		Rotate(float rotationSpeed);
		~Rotate() override = default;

		Rotate(const Rotate& other)					= delete;
		Rotate(Rotate&& other) noexcept				= delete;
		Rotate& operator=(const Rotate& other)		= delete;
		Rotate& operator=(Rotate&& other) noexcept	= delete;

		void OnEnter() override;
		void OnExit() override;
		void Update() override;
		std::string TransitionState() override;

	private:
		const float m_RotationSpeed{};
		float m_Rotation{};
	};

	class TargetPlayer : public GameObjectState
	{
	public:
		TargetPlayer() = default;
		~TargetPlayer() override = default;

		TargetPlayer(const TargetPlayer& other)					= delete;
		TargetPlayer(TargetPlayer&& other) noexcept				= delete;
		TargetPlayer& operator=(const TargetPlayer& other)		= delete;
		TargetPlayer& operator=(TargetPlayer&& other) noexcept	= delete;

		std::string TransitionState() override;

	private:
	};
}
