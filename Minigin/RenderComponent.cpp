#include "RenderComponent.h"
#include "ResourceManager.h"

using namespace dae;

RenderComponent::RenderComponent()
{
}

RenderComponent::~RenderComponent()
{
}

void RenderComponent::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0);
}
