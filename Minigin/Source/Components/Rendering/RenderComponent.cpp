#include "RenderComponent.h"

#include <windows.h>

#include "GameObject.h"
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
	m_Depth = GetOwner().GetWorldPosition().z;
	Renderer::GetInstance().RegisterRenderComponent(this);
}

void RenderComponent::LateUpdate()
{
	const float newDepth{ GetOwner().GetWorldPosition().z };
	
	if (abs(m_Depth - newDepth) > FLT_EPSILON)
	{
		m_Depth = newDepth;
		Renderer::GetInstance().FlagDepthDirty();
	}
}

Texture2D* RenderComponent::GetTexture() const
{
	return m_TexturePtr;
}

glm::vec2 RenderComponent::GetRenderPosition() const
{
	glm::vec3 position{ GetOwner().GetWorldPosition() };
	position.x -= m_Anchor.x * GetTextureWidth();
	position.y -= m_Anchor.y * GetTextureHeight();
	return { position.x, position.y };
}

float RenderComponent::GetRenderDepth() const
{
	return m_Depth;
}

void RenderComponent::SetTexture(Texture2D* texturePtr)
{
	m_TexturePtr = texturePtr;
}

void RenderComponent::SetAnchor(const glm::vec2& anchor)
{
	m_Anchor = anchor;
}

int RenderComponent::GetTextureWidth() const
{
	return m_TexturePtr->GetSize().x;
}

int RenderComponent::GetTextureHeight() const
{
	return m_TexturePtr->GetSize().y;
}
