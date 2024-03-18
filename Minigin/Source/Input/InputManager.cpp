#include <SDL.h>
#include "InputManager.h"

#include "Controller.h"
#include "DebugUtils.h"
#include "GUI.h"
#include "KeyboardInput.h"


using namespace mk;

bool InputManager::ProcessInput()
{
	SDL_Event e;

	while (SDL_PollEvent(&e)) 
	{
		GUI::GetInstance().ProcessSDLEvents(e);
		//if (GUI::GetInstance().ProcessSDLEvents(e))
		//	return true;

		Controller::PollKeyboard(e);

		if (e.type == SDL_QUIT)
			return false;
	}

	for (const auto& controller : m_Controllers)
		controller->HandleInput();

	Controller::FlushKeyboard();

	return true;
}

Controller* InputManager::AddController()
{
	m_Controllers.emplace_back(std::make_unique<Controller>(m_Idx));
	++m_Idx;
	return m_Controllers.back().get();
}
