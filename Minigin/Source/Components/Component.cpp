#include "Component.h"

using namespace mk;

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

Component::Component(GameObject* ownerPtr)
	: m_OwnerPtr{ ownerPtr }
{
}

GameObject& Component::GetOwner() const
{
	return *m_OwnerPtr;
}
