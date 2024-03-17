#pragma once
#include <memory>
#include "ControllerInput.h"
#include "KeyboardInput.h"
#include "InputMapping.h"

namespace mk
{
	class Controller final
	{
	public:
		Controller(int idx);
		~Controller() = default;

		Controller(const Controller& other)					= default;
		Controller(Controller&& other) noexcept				= default;
		Controller& operator=(const Controller& other)		= default;
		Controller& operator=(Controller&& other) noexcept	= default;

		void PollKeyboard(const SDL_Event& event);
		void HandleInput();

		int GetIdx() const;
		InputMapping& GetInputMapping();

		void SetInputMapping(InputMapping map);

	private:
		int m_Idx{};

		KeyboardInput m_Keyboard{};
		ControllerInput m_Controller{};
		InputMapping m_InputMapping{};
	};
}
