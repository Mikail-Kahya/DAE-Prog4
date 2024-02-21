#include "Component.h"

Component::Component(const std::string& name)
	: m_Name{ name }
{
}

void Component::Destroy()
{
	m_Destroy = true;
}

void Component::ClearDestroy()
{
	m_Destroy = false;
}

bool Component::DestroyFlagged() const
{
	return m_Destroy;
}