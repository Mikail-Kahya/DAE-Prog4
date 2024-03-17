#pragma once
#include <memory>
#include "glm/vec2.hpp"
#include "Input.h"
#include "XControllerInput.h"

namespace mk
{
	//class XControllerInput;

	class ControllerInput final
	{
	public:
		ControllerInput();
		~ControllerInput() = default;

		ControllerInput(const ControllerInput& other)					= delete;
		ControllerInput(ControllerInput&& other) noexcept				= default;
		ControllerInput& operator=(const ControllerInput& other)		= delete;
		ControllerInput& operator=(ControllerInput&& other) noexcept	= default;

		void UpdateInput();
		// Deadzone is in a range between 0 and 1
		void SetDeadzone(float deadzone);

		glm::vec2 GetLeftStickInput() const noexcept;
		glm::vec2 GetRightStickInput() const noexcept;
		glm::vec2 GetDPadInput() const noexcept;

		bool ButtonDown(Input input) const noexcept;
		bool ButtonHold(Input input) const noexcept;
		bool ButtonUp(Input input) const noexcept;

	private:
		std::unique_ptr<XControllerInput> m_XInputImpl;
	};
}
