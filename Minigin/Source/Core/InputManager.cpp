#include <SDL.h>
#include "InputManager.h"

#include "Controller.h"
#include "DebugUtils.h"
#include "GUI.h"


using namespace mk;

bool InputManager::ProcessInput()
{
	SDL_Event e;

	while (SDL_PollEvent(&e)) 
	{
		for (const auto& controller : m_Controllers)
			controller->PollKeyboard(e);

		if (GUI::GetInstance().ProcessSDLEvents(e))
			return true;

		if (e.type == SDL_QUIT)
			return false;
	}

	for (const auto& controller : m_Controllers)
		controller->HandleInput();

	return true;
}

void InputManager::AddController()
{
	m_Controllers.emplace_back(std::make_unique<Controller>(0));
}
