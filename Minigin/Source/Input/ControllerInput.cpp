#include "ControllerInput.h"

mk::ControllerInput::ControllerInput()
	: m_XInputImpl{ std::make_unique<XControllerInput>() }
{
}

void mk::ControllerInput::UpdateInput()
{
	m_XInputImpl->UpdateInput();
}

void mk::ControllerInput::SetDeadzone(float deadzone)
{
	m_XInputImpl->SetDeadzone(deadzone);
}

glm::vec2 mk::ControllerInput::GetLeftStickInput() const noexcept
{
	return m_XInputImpl->GetLeftStickInput();
}

glm::vec2 mk::ControllerInput::GetRightStickInput() const noexcept
{
	return m_XInputImpl->GetRightStickInput();
}

glm::vec2 mk::ControllerInput::GetDPadInput() const noexcept
{
	glm::vec2 input{};
	if (ButtonHold(Input::dPadLeft))
		--input.x;

	if (ButtonHold(Input::dPadRight))
		++input.x;

	if (ButtonHold(Input::dPadDown))
		--input.y;

	if (ButtonHold(Input::dPadUp))
		++input.y;

	return input;
}

bool mk::ControllerInput::ButtonDown(Input input) const noexcept
{
	return m_XInputImpl->ButtonDown(input);
}

bool mk::ControllerInput::ButtonHold(Input input) const noexcept
{
	return m_XInputImpl->ButtonHold(input);
}

bool mk::ControllerInput::ButtonUp(Input input) const noexcept
{
	return m_XInputImpl->ButtonUp(input);
}
