#include <SDL.h>
#include "InputManager.h"

#include "GUI.h"
#include "XController.h"

bool mk::InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}

		GUI::GetInstance().AddSdlEvents(e);
	}

	m_Controller->UpdateInput();

	return true;
}
