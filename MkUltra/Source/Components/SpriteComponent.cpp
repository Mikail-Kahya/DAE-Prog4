#include "SpriteComponent.h"

#include "GameObject.h"
#include "ResourceManager.h"
#include "RenderComponent.h"

using namespace mk;

SpriteComponent::SpriteComponent(const std::string& file)
{
	m_TexturePtr = ResourceManager::GetInstance().LoadTexture(file);
}

void SpriteComponent::Start()
{
    m_RendererPtr = GetOwner()->AddComponent<RenderComponent>(m_TexturePtr);
}

void SpriteComponent::SetTexture(const std::string& file)
{
	m_TexturePtr = ResourceManager::GetInstance().LoadTexture(file);
	m_RendererPtr->SetTexture(m_TexturePtr);
}
