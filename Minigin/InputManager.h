#pragma once
#include <memory>
#include <vector>

#include "Singleton.h"
#include "Controller.h"

namespace mk
{
	//class Controller;

	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager() = default;

		bool ProcessInput();
		Controller* AddController();
		void RemoveController(Controller* controllerPtr);

	private:
		uint8_t m_Idx{};
		std::vector<Controller> m_Controllers;
	};

}
