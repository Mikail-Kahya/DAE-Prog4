#pragma once
#include "Singleton.h"

namespace mk
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
	};

}
