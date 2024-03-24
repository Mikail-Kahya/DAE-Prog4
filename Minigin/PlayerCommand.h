#pragma once
#include "Command.h"
#include "Observer.h"
#include "glm/vec2.hpp"

namespace mk
{
	class MovementComponent;

	class MoveCommand : public GameObjectCommand
	{
	public:
		MoveCommand(GameObject* gameObject, const glm::vec2& direction);
		~MoveCommand() override = default;

		MoveCommand(const MoveCommand& other)					= delete;
		MoveCommand(MoveCommand&& other) noexcept				= delete;
		MoveCommand& operator=(const MoveCommand& other)		= delete;
		MoveCommand& operator=(MoveCommand&& other) noexcept	= delete;

		void Execute() override;

	private:
		const glm::vec2 m_Direction{};
		MovementComponent* m_MoveComp{};
	};


	class FireCommand : public GameObjectCommand
	{
	public:
		FireCommand(GameObject* gameObject);
		~FireCommand() override = default;

		FireCommand(const FireCommand& other) = delete;
		FireCommand(FireCommand&& other) noexcept = delete;
		FireCommand& operator=(const FireCommand& other) = delete;
		FireCommand& operator=(FireCommand&& other) noexcept = delete;

		void Execute() override;
	};
}
