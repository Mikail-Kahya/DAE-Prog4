#include <SDL.h>
#include "InputManager.h"

#include "DebugUtils.h"
#include "GUI.h"
#include "XController.h"


using namespace mk;

InputManager::InputManager()
	: m_Controller{ std::make_unique<XController>() }
{
}

bool InputManager::ProcessInput()
{
	SDL_Event e;

	while (SDL_PollEvent(&e)) {
		m_Keyboard.Update(e);
		if (GUI::GetInstance().ProcessSDLEvents(e))
			return true;

		if (e.type == SDL_QUIT) {
			return false;
		}
	}

	m_Controller->UpdateInput();


	m_Keyboard.Flush();

	return true;
}
