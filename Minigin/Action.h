#pragma once
#include "Controller.h"
#include "SDL_scancode.h"

namespace mk
{
	class Keyboard;
	class Command;

	class Action final
	{
	public:
		enum class Type : uint8_t
		{
			hold,
			down,
			up
		};

		Action() = default;
		~Action() = default;

		Action(const Action& other)					= default;
		Action(Action&& other) noexcept				= default;
		Action& operator=(const Action& other)		= default;
		Action& operator=(Action&& other) noexcept	= default;

		void SetControllerInput(Controller::Input button);
		void SetKeyboardInput(SDL_Scancode button);
		void SetType(Type inputType);
		bool Triggered(const Controller& controller, const Keyboard& keyboard) const;

	private:
		Controller::Input m_ControllerInput{};
		SDL_Scancode m_KeyboardInput{};
		Type m_Type{};
	};
}
