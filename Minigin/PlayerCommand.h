#pragma once
#include "Command.h"
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
}
