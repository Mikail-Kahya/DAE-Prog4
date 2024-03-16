#pragma once

namespace mk
{
	class Command
	{
	public:
		Command() = default;
		virtual ~Command() = default;

		Command(const Command& other)					= delete;
		Command(Command&& other) noexcept				= delete;
		Command& operator=(const Command& other)		= delete;
		Command& operator=(Command&& other)	noexcept	= delete;

		virtual void Execute() = 0;
	};

	/*class GameActorCommand : public Command
	{
	public:
		GameActorCommand() = default;
		~GameActorCommand() override = default;

		GameActorCommand(const GameActorCommand& other) = delete;
		GameActorCommand(GameActorCommand&& other) noexcept = delete;
		GameActorCommand& operator=(const GameActorCommand& other) = delete;
		GameActorCommand& operator=(GameActorCommand&& other)	noexcept = delete;
	};*/
}