#pragma once
#include "glm/vec2.hpp"

namespace mk
{
	class Controller
	{
	public:
		enum class Input : uint8_t
		{
			a,
			b,
			y,
			x,
			dPadLeft,
			dPadRight,
			dPadDown,
			dPadUp,
			stickLeft,
			stickRight,
			triggerLeft,
			triggerRight,
			bumperLeft,
			bumperRight
		};

		Controller() = default;
		virtual ~Controller() = default;

		Controller(const Controller& other)					= delete;
		Controller(Controller&& other) noexcept				= delete;
		Controller& operator=(const Controller& other)		= delete;
		Controller& operator=(Controller&& other) noexcept	= delete;

		virtual void UpdateInput() = 0;
		// Deadzone is in a range between 0 and 1
		virtual void SetDeadzone(float deadzone) = 0;

		virtual glm::vec2 GetLeftStickInput() const noexcept = 0;
		virtual glm::vec2 GetRightStickInput() const noexcept = 0;
		virtual glm::vec2 GetDPadInput() const noexcept
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

		virtual bool ButtonDown(Input input) const noexcept = 0;
		virtual bool ButtonHold(Input input) const noexcept = 0;
		virtual bool ButtonUp(Input input) const noexcept = 0;
	};
}
