#pragma once
#include "Command.h"

namespace mk
{
	class MoveUpCommand : public GameObjectCommand
	{
	public:
		MoveUpCommand(GameObject* gameObject);
		~MoveUpCommand() override = default;

		MoveUpCommand(const MoveUpCommand& other) = delete;
		MoveUpCommand(MoveUpCommand&& other) noexcept = delete;
		MoveUpCommand& operator=(const MoveUpCommand& other) = delete;
		MoveUpCommand& operator=(MoveUpCommand&& other) noexcept = delete;

		void Execute() override;
	};
}