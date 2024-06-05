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
	m_Depth = GetOwner()->GetWorldDepth();
	Renderer::GetInstance().RegisterRenderComponent(this);
}

void RenderComponent::LateUpdate()
{
	const float newDepth{ GetOwner()->GetWorldDepth() };
	
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
	glm::vec2 position{ GetOwner()->GetWorldPosition() };
	position.x -= m_Anchor.x * m_Width;
	position.y -= m_Anchor.y * m_Height;
	return { position.x, position.y };
}

float RenderComponent::GetRenderDepth() const
{
	return m_Depth;
}

std::pair<bool, bool> RenderComponent::IsFlipped() const
{
	return m_FlipAxis;
}

const glm::vec2& RenderComponent::GetAnchor() const
{
	return m_Anchor;
}

float RenderComponent::GetWidth() const
{
	return m_Width;
}

float RenderComponent::GetHeight() const
{
	return m_Height;
}


void RenderComponent::SetTexture(Texture2D* texturePtr, bool useTextureSize)
{
	m_TexturePtr = texturePtr;
	if (useTextureSize)
	{
		const glm::vec2 size{ texturePtr->GetSize() };
		SetWidth(size.x);
		SetHeight(size.y);
	}
}

void RenderComponent::SetAnchor(const glm::vec2& anchor)
{
	m_Anchor = anchor;
}

void RenderComponent::SetFlipHorizontal(bool isFlipped)
{
	m_FlipAxis.first = isFlipped;
}

void RenderComponent::SetFlipVertical(bool isFlipped)
{
	m_FlipAxis.second = isFlipped;
}

void RenderComponent::SetWidth(float width)
{
	m_Width = width;
}

void RenderComponent::SetHeight(float height)
{
	m_Height = height;
}