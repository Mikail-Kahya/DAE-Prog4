#include "RenderComponent.h"

#include <GameObject.h>

#include "Renderer.h"
#include "ResourceManager.h"

using namespace mk;

RenderComponent::RenderComponent(Texture2D* texturePtr)
	: m_TexturePtr{ texturePtr }
{
}

RenderComponent::RenderComponent(const std::string& file)
{
	m_TexturePtr = ResourceManager::GetInstance().LoadTexture(file);
}

RenderComponent::~RenderComponent()
{
	Renderer::GetInstance().UnregisterRenderComponent(this);
}

void RenderComponent::Start()
{
	Renderer::GetInstance().RegisterRenderComponent(this);
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