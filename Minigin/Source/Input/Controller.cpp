#include "Controller.h"

#include "Command.h"
#include "KeyboardInput.h"

using namespace mk;

Controller::Controller(uint8_t idx)
	: m_Idx{ idx }
	, m_Controller{ idx }
{
}

void Controller::HandleInput()
{
	const KeyboardInput& keyboard{ KeyboardInput::GetInstance() };

	m_Controller.UpdateInput();
	for (const auto& mapping : m_InputMapping.GetMappings())
	{
		if (mapping.first.Triggered(m_Controller, keyboard))
			mapping.second->Execute();
	}
}

uint8_t Controller::GetIdx() const
{
	return m_Idx;
}

InputMapping& Controller::GetInputMapping()
{
	return m_InputMapping;
}

void Controller::SetInputMapping(InputMapping&& map)
{
	m_InputMapping = std::move(map);
}
