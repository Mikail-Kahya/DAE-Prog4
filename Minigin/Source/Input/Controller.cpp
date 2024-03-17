#include "Controller.h"

#include "Command.h"


using namespace mk;

Controller::Controller(int idx)
	: m_Idx{ idx }
{
}

void Controller::PollKeyboard(const SDL_Event& event)
{
	m_Keyboard.Update(event);
}

void Controller::HandleInput()
{
	for (const auto& mapping : m_InputMapping.GetMappings())
	{
		if (mapping.second.Triggered(m_Controller, m_Keyboard))
			mapping.first->Execute();
	}

	m_Keyboard.Flush();
}

int Controller::GetIdx() const
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
