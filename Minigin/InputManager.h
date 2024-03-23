#pragma once
#include <memory>
#include <vector>

#include "InputMapping.h"
#include "Singleton.h"
#include "Controller.h"

namespace mk
{
	class Command;

	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager() = default;

		bool ProcessInput();
		Controller* AddController();
		void RemoveController(Controller* controllerPtr);

		template<std::derived_from<Command> CommandType, typename... Args>
		Command* AddCommand(const Args&... args)
		{
			m_Commands.emplace_back(std::make_unique<CommandType>(args...));
			return m_Commands.back().get();
		}

		void RemoveCommand(Command* commandPtr);

	private:
		uint8_t m_Idx{};
		std::vector<Controller> m_Controllers;
		std::vector<std::unique_ptr<Command>> m_Commands;
	};

}
