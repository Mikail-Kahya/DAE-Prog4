#pragma once
#include <map>
#include <memory>
#include <vector>

#include "Singleton.h"

#include "XController.h"
#include "Keyboard.h"

namespace mk
{
	class Action;
	class Controller;
	class Command;
	class Keyboard;

	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager();

		bool ProcessInput();

	private:
		std::unique_ptr<Controller> m_Controller;
		Keyboard m_Keyboard{};
	};

}
