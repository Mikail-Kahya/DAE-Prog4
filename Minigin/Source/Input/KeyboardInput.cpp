#include "KeyboardInput.h"

#include <algorithm>

using namespace mk;

KeyboardInput::KeyboardInput()
{
	m_PrevKeys.resize(SDL_NUM_SCANCODES);
	m_CurrentKeys.resize(SDL_NUM_SCANCODES);
}

void KeyboardInput::Flush()
{
	m_PrevKeys = std::move(m_CurrentKeys);
	m_CurrentKeys.resize(SDL_NUM_SCANCODES);
}

void KeyboardInput::Update(const SDL_Event& sdlEvent)
{
	switch (sdlEvent.type)
	{
	case SDL_KEYDOWN:
		m_CurrentKeys[sdlEvent.key.keysym.scancode] = true;
		break;
	case SDL_KEYUP:
		m_CurrentKeys[sdlEvent.key.keysym.scancode] = false;
		break;
	}
}

bool KeyboardInput::ButtonDown(SDL_Scancode key) const
{
	return !m_PrevKeys[key] && m_CurrentKeys[key];
}

bool KeyboardInput::ButtonHold(SDL_Scancode key) const
{
	return m_CurrentKeys[key];
}

bool KeyboardInput::ButtonUp(SDL_Scancode key) const
{
	//return m_UpKeys[SDL_SCANCODE_TO_KEYCODE(key)];
	return m_PrevKeys[key] && !m_CurrentKeys[key];
}