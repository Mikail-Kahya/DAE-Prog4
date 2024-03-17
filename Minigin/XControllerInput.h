#pragma once
#include "Input.h"

#define WIN32_LEAN_AND_MEAN
#include <functional>
#include <windows.h>
#include <Xinput.h>

#include "glm/vec2.hpp"

namespace mk
{
	class XControllerInput final
	{
	public:
		XControllerInput();
		~XControllerInput();

		XControllerInput(const XControllerInput& other)					= delete;
		XControllerInput(XControllerInput&& other) noexcept				= delete;
		XControllerInput& operator=(const XControllerInput& other)		= delete;
		XControllerInput& operator=(XControllerInput&& other) noexcept	= delete;

		void UpdateInput();
		// Deadzone is in a range between 0 and 1
		void SetDeadzone(float deadzone);

		glm::vec2 GetLeftStickInput() const noexcept;
		glm::vec2 GetRightStickInput() const noexcept;
		bool ButtonDown(Input input) const noexcept;
		bool ButtonHold(Input input) const noexcept;
		bool ButtonUp(Input input) const noexcept;

	private:
		glm::vec2 GetStickInput(SHORT xInput, SHORT yInput) const noexcept;

		bool XHandleInput(const std::function<bool(int)>& func, Input input) const noexcept;
		bool XButtonPressed(int input) const noexcept;
		bool XButtonDown(int input) const noexcept;
		bool XButtonReleased(int input) const noexcept;

		static constexpr int MAX_STICK_INPUT { 32767 };
		float m_Deadzone{};

		XINPUT_STATE m_PreviousState{};
		XINPUT_STATE m_CurrentState{};
		int m_ControllerIdx{};
	};
}
