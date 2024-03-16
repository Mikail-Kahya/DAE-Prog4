#pragma once
#include "Controller.h"

#define WIN32_LEAN_AND_MEAN
#include <functional>
#include <windows.h>
#include <Xinput.h>

namespace mk
{
	class XController final : public Controller
	{
	public:
		XController();
		~XController() override;

		XController(const XController& other)					= delete;
		XController(XController&& other) noexcept				= delete;
		XController& operator=(const XController& other)		= delete;
		XController& operator=(XController&& other)	noexcept	= delete;

		void UpdateInput() override;
		// Deadzone is in a range between 0 and 1
		void SetDeadzone(float deadzone) override;

		glm::vec2 GetLeftStickInput() const noexcept override;
		glm::vec2 GetRightStickInput() const noexcept override;
		bool ButtonDown(Input input) const noexcept override;
		bool ButtonHold(Input input) const noexcept override;
		bool ButtonUp(Input input) const noexcept override;

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