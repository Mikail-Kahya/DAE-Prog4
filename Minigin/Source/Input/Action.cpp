#include "Action.h"

#include "Keyboard.h"
#include "SDL_keycode.h"

using namespace mk;

void Action::SetControllerInput(Controller::Input button)
{
	m_ControllerInput = button;
}

void Action::SetKeyboardInput(SDL_Scancode button)
{
	m_KeyboardInput = button;
}

void Action::SetType(Type inputType)
{
	m_Type = inputType;
}

bool Action::Triggered(const Controller& controller, const Keyboard& keyboard) const
{
	switch (m_Type)
	{
	case Type::down:
		return keyboard.ButtonDown(m_KeyboardInput) || controller.ButtonDown(m_ControllerInput);
	case Type::hold:
		return keyboard.ButtonHold(m_KeyboardInput) || controller.ButtonHold(m_ControllerInput);
	case Type::up:
		return keyboard.ButtonUp(m_KeyboardInput) || controller.ButtonUp(m_ControllerInput);
	}
	return false;
}
