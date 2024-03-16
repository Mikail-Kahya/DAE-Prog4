#include "Action.h"

using namespace mk;

void Action::SetControllerInput(Controller::Input button)
{
	m_ControllerInput = button;
}

void Action::SetType(Type inputType)
{
	m_Type = inputType;
}

bool Action::Triggered(const Controller& controller) const
{
	switch (m_Type)
	{
	case Type::pressed:
		return controller.ButtonPressed(m_ControllerInput);
	case Type::down:
		return controller.ButtonDown(m_ControllerInput);
	case Type::released:
		return controller.ButtonReleased(m_ControllerInput);
	}
	return false;
}
