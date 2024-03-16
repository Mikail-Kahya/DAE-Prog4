#include "XController.h"

#include <windows.h>
#pragma comment(lib, "xinput.lib")

void mk::XController::UpdateInput()
{
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(m_ControllerIdx, &m_CurrentState);
}

glm::vec2 mk::XController::GetLeftStickInput() const
{
	return {
		static_cast<float>(m_CurrentState.Gamepad.sThumbLX) / MAX_STICK_INPUT,
		static_cast<float>(m_CurrentState.Gamepad.sThumbLY) / MAX_STICK_INPUT
	};
}

glm::vec2 mk::XController::GetRightStickInput() const
{
	return {
		static_cast<float>(m_CurrentState.Gamepad.sThumbRX) / MAX_STICK_INPUT,
		static_cast<float>(m_CurrentState.Gamepad.sThumbRY) / MAX_STICK_INPUT
	};
}
