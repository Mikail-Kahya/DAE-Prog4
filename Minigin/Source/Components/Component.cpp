#include "Component.h"

using namespace mk;

void Component::SetOwner(GameObject* ownerPtr)
{
	m_OwnerPtr = ownerPtr;
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

GameObject& Component::GetOwner() const
{
	return *m_OwnerPtr;
}
