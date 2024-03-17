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
	KeyboardInput& keyboard{ KeyboardInput::GetInstance() };

	while (SDL_PollEvent(&e)) 
	{
		keyboard.Update(e);

		if (GUI::GetInstance().ProcessSDLEvents(e))
			return true;

		if (e.type == SDL_QUIT)
			return false;
	}

	for (const auto& controller : m_Controllers)
		controller->HandleInput();

	keyboard.Flush();

	return true;
}

Controller* InputManager::AddController()
{
	m_Controllers.emplace_back(std::make_unique<Controller>(m_Idx));
	++m_Idx;
	return m_Controllers.back().get();
}
