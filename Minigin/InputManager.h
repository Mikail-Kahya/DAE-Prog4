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

	private:
		uint8_t m_Idx{};
		std::vector<std::unique_ptr<Controller>> m_Controllers;
	};

}
