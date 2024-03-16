#pragma once
#include <map>
#include <memory>
#include <vector>

#include "Singleton.h"

#include "XController.h"
#include "Command.h"
#include "Action.h"

namespace mk
{
	class Action;
	class Controller;
	class Command;

	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager();

		bool ProcessInput();

	private:
		std::unique_ptr<Controller> m_Controller;
		std::vector<std::unique_ptr<Command>> m_Commands;
		std::vector<std::unique_ptr<Action>> m_Actions;
	};

}
