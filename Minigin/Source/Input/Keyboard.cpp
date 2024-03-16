#include "Keyboard.h"

#include <algorithm>

#include "DebugUtils.h"

using namespace mk;

Keyboard::Keyboard()
{
	m_PrevKeys.resize(SDL_NUM_SCANCODES);
	m_CurrentKeys.resize(SDL_NUM_SCANCODES);
}

void Keyboard::Flush()
{
	m_PrevKeys = std::move(m_CurrentKeys);
	m_CurrentKeys.resize(SDL_NUM_SCANCODES);
}

void Keyboard::Update(const SDL_Event& sdlEvent)
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

bool Keyboard::ButtonDown(SDL_Scancode key) const
{
	return !m_PrevKeys[key] && m_CurrentKeys[key];
}

bool Keyboard::ButtonHold(SDL_Scancode key) const
{
	return m_CurrentKeys[key];
}

bool Keyboard::ButtonUp(SDL_Scancode key) const
{
	//return m_UpKeys[SDL_SCANCODE_TO_KEYCODE(key)];
	return m_PrevKeys[key] && !m_CurrentKeys[key];
}