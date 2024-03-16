#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Xinput.h>

#include "glm/vec2.hpp"
//#pragma comment(lib, "xinput.lib")

namespace mk
{
	class XController
	{
	public:
		XController() = default;
		~XController() = default;

		XController(const XController& other)					= delete;
		XController(XController&& other) noexcept				= delete;
		XController& operator=(const XController& other)		= delete;
		XController& operator=(XController&& other)	noexcept	= delete;

		void UpdateInput();

		glm::vec2 GetLeftStickInput() const;
		glm::vec2 GetRightStickInput() const;

	private:
		constexpr int MAX_STICK_INPUT { 32767 };

		XINPUT_STATE m_CurrentState{};
		int m_ControllerIdx{};
	};
}