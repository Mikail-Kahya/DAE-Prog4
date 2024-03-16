#pragma once
#include <memory>

#include "Singleton.h"

namespace mk
{
	class XController;

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();

	private:
		std::unique_ptr<XController> m_Controller;
	};

}
