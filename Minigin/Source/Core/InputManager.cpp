#include <SDL.h>
#include "InputManager.h"

#include "DebugUtils.h"
#include "GUI.h"
#include "XController.h"
#include "Command.h"
#include "Action.h"

using namespace mk;

InputManager::InputManager()
	: m_Controller{ std::make_unique<XController>() }
{
}

bool InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (GUI::GetInstance().ProcessSDLEvents(e))
			return true;

		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			
		}
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			
		}
	}

	m_Controller->UpdateInput();
	const glm::vec2 leftStick{ m_Controller->GetDPadInput() };

	if (m_Controller->ButtonDown(Controller::Input::b))
		Print("X: " + std::to_string(leftStick.x) + "\t Y:" + std::to_string(leftStick.y) + "\n");

	return true;
}
