#include "RenderComponent.h"
#include "Renderer.h"

using namespace mk;

RenderComponent::RenderComponent()
{
	Renderer::GetInstance().RegisterRenderComponent(this);
}

RenderComponent::~RenderComponent()
{
	Renderer::GetInstance().UnregisterRenderComponent(this);
}

void RenderComponent::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0);
}

const Transform& RenderComponent::GetTransform() const
{
	return m_Transform;
}
