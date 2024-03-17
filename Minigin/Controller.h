#pragma once
#include "ControllerInput.h"
#include "InputMapping.h"
#include "SDL_events.h"

namespace mk
{
	class Controller final
	{
	public:
		Controller(uint8_t idx);
		~Controller() = default;

		Controller(const Controller& other)					= delete;
		Controller(Controller&& other) noexcept				= default;
		Controller& operator=(const Controller& other)		= delete;
		Controller& operator=(Controller&& other) noexcept	= default;

		void HandleInput();

		uint8_t GetIdx() const;
		InputMapping& GetInputMapping();

		void SetInputMapping(InputMapping&& map);

	private:
		uint8_t m_Idx{};

		ControllerInput m_Controller;
		InputMapping m_InputMapping{};
	};
}
