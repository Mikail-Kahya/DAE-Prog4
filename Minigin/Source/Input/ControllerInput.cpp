#include "ControllerInput.h"
#include "XControllerInput.h"

using namespace mk;

ControllerInput::ControllerInput(uint8_t idx)
	: m_XInputImpl{ new XControllerInput(idx) }
{
}

ControllerInput::~ControllerInput()
{
	delete m_XInputImpl;
}

ControllerInput::ControllerInput(ControllerInput&& other) noexcept
	: m_XInputImpl{ other.m_XInputImpl }
{
	other.m_XInputImpl = nullptr;
}

ControllerInput& ControllerInput::operator=(ControllerInput&& other) noexcept
{
	m_XInputImpl = other.m_XInputImpl;
	other.m_XInputImpl = nullptr;

	return *this;
}

void ControllerInput::UpdateInput()
{
	m_XInputImpl->UpdateInput();
}

void ControllerInput::SetDeadzone(float deadzone)
{
	m_XInputImpl->SetDeadzone(deadzone);
}

glm::vec2 ControllerInput::GetLeftStickInput() const noexcept
{
	return m_XInputImpl->GetLeftStickInput();
}

glm::vec2 ControllerInput::GetRightStickInput() const noexcept
{
	return m_XInputImpl->GetRightStickInput();
}

glm::vec2 ControllerInput::GetDPadInput() const noexcept
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

bool ControllerInput::ButtonDown(Input input) const noexcept
{
	return m_XInputImpl->ButtonDown(input);
}

bool ControllerInput::ButtonHold(Input input) const noexcept
{
	return m_XInputImpl->ButtonHold(input);
}

bool ControllerInput::ButtonUp(Input input) const noexcept
{
	return m_XInputImpl->ButtonUp(input);
}
