#include "RenderComponent.h"

#include <GameObject.h>

#include "Renderer.h"

using namespace mk;

RenderComponent::RenderComponent(Texture2D* texturePtr)
	: m_TexturePtr{ texturePtr }
{
	Renderer::GetInstance().RegisterRenderComponent(this);
}

RenderComponent::~RenderComponent()
{
	Renderer::GetInstance().UnregisterRenderComponent(this);
}

const Transform& RenderComponent::GetTransform() const
{
	return GetOwner().GetTransform();
}

Texture2D* RenderComponent::GetTexture() const
{
	return m_TexturePtr;
}

void RenderComponent::SetTexture(Texture2D* texturePtr)
{
	m_TexturePtr = texturePtr;
}
