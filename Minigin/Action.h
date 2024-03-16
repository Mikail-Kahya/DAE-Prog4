#pragma once
#include "Controller.h"

namespace mk
{
	class Command;

	class Action final
	{
	public:
		enum class Type : uint8_t
		{
			pressed,
			down,
			released
		};

		Action() = default;
		~Action() = default;

		Action(const Action& other)					= default;
		Action(Action&& other) noexcept				= default;
		Action& operator=(const Action& other)		= default;
		Action& operator=(Action&& other) noexcept	= default;

		void SetControllerInput(Controller::Input button);
		void SetType(Type inputType);
		bool Triggered(const Controller& controller) const;

	private:
		Controller::Input m_ControllerInput{};
		Type m_Type{};
	};
}