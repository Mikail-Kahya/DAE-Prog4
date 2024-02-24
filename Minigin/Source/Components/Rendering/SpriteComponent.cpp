#include "SpriteComponent.h"
#include "ResourceManager.h"

using namespace mk;

SpriteComponent::SpriteComponent(GameObject* ownerPtr)
	: RenderComponent(ownerPtr)
{
}

void SpriteComponent::SetTexture(const std::string& file)
{
	m_TexturePtr = ResourceManager::GetInstance().LoadTexture(file);
}

Texture2D* SpriteComponent::GetTexture() const
{
	return m_TexturePtr;
}
