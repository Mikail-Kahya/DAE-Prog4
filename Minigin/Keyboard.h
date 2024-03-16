#pragma once
#include <vector>

#include "SDL_events.h"

namespace mk
{
	class Keyboard final
	{
	public:
		Keyboard();
		~Keyboard() = default;

		Keyboard(const Keyboard& other)					= default;
		Keyboard(Keyboard&& other) noexcept				= default;
		Keyboard& operator=(const Keyboard& other)		= default;
		Keyboard& operator=(Keyboard&& other) noexcept	= default;

		void Flush();
		void Update(const SDL_Event& sdlEvent);

		bool ButtonDown(SDL_Scancode key) const;
		bool ButtonHold(SDL_Scancode key) const;
		bool ButtonUp(SDL_Scancode key) const;

	private:
		std::vector<bool> m_PrevKeys{};
		std::vector<bool> m_CurrentKeys{};
	};
}