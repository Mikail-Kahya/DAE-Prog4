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

void RenderComponent::SetPosition(float x, float y, float z)
{
	if (z < FLT_EPSILON)
		z = Renderer::GetInstance().GetNextDepth();

	m_Transform.SetPosition(x, y, z);
}

const Transform& RenderComponent::GetTransform() const
{
	return m_Transform;
}
