#include "XController.h"

#include <cmath>

using namespace mk;

XController::XController()
{
	constexpr float defaultDeadZone{ 0.05f };
	SetDeadzone(defaultDeadZone);
}

XController::~XController()
{
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_PreviousState, sizeof(XINPUT_STATE));
}

void XController::UpdateInput()
{
	CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(m_ControllerIdx, &m_CurrentState);
}

void XController::SetDeadzone(float deadzone)
{
	m_Deadzone = deadzone * MAX_STICK_INPUT;
}

glm::vec2 XController::GetLeftStickInput() const noexcept
{
	return GetStickInput(m_CurrentState.Gamepad.sThumbLX, m_CurrentState.Gamepad.sThumbLY);
}

glm::vec2 XController::GetRightStickInput() const noexcept
{
	return GetStickInput(m_CurrentState.Gamepad.sThumbRX, m_CurrentState.Gamepad.sThumbRY);
}

bool XController::ButtonDown(Input input) const noexcept
{
	return XHandleInput([this](int input)
		{
			return XButtonPressed(input);
		}, input);
}

bool XController::ButtonHold(Input input) const noexcept
{
	return XHandleInput([this](int input)
		{
			return XButtonDown(input);
		}, input);
}

bool XController::ButtonUp(Input input) const noexcept
{
	return XHandleInput([this](int xInput)
		{
			return XButtonReleased(xInput);
		}, input);
}

glm::vec2 XController::GetStickInput(SHORT xInput, SHORT yInput) const noexcept
{
	float x{ static_cast<float>(xInput) };
	if (abs(x) < m_Deadzone)
		x = 0;

	float y{ static_cast<float>(yInput) };
	if (abs(y) < m_Deadzone)
		y = 0;

	return { x / MAX_STICK_INPUT, y / MAX_STICK_INPUT };
}

bool XController::XHandleInput(const std::function<bool(int)>& press, Input input) const noexcept
{
	switch (input) {
	case Input::a:
		return press(XINPUT_GAMEPAD_A);
	case Input::b:
		return press(XINPUT_GAMEPAD_B);
	case Input::y:
		return press(XINPUT_GAMEPAD_Y);
	case Input::x:
		return press(XINPUT_GAMEPAD_X);
	case Input::dPadLeft:
		return press(XINPUT_GAMEPAD_DPAD_LEFT);
	case Input::dPadRight:
		return press(XINPUT_GAMEPAD_DPAD_RIGHT);
	case Input::dPadDown:
		return press(XINPUT_GAMEPAD_DPAD_DOWN);
	case Input::dPadUp:
		return press(XINPUT_GAMEPAD_DPAD_UP);
	case Input::bumperLeft:
		return press(XINPUT_GAMEPAD_LEFT_SHOULDER);
	case Input::bumperRight:
		return press(XINPUT_GAMEPAD_RIGHT_SHOULDER);
	}
	return false;
}

bool XController::XButtonPressed(int input) const noexcept
{
	return !(m_PreviousState.Gamepad.wButtons & input) *
			(m_CurrentState.Gamepad.wButtons & input);
}

bool XController::XButtonDown(int input) const noexcept
{
	return m_CurrentState.Gamepad.wButtons & input;
}
 
bool XController::XButtonReleased(int input) const noexcept
{
	return	 (m_PreviousState.Gamepad.wButtons & input) *
			!(m_CurrentState.Gamepad.wButtons & input);
}
