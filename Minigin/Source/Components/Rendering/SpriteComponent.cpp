#include "SpriteComponent.h"
#include "ResourceManager.h"

using namespace mk;

void SpriteComponent::SetTexture(const std::string& file)
{
	m_TexturePtr = ResourceManager::GetInstance().LoadTexture(file);
}

Texture2D* SpriteComponent::GetTexture() const
{
	return m_TexturePtr;
}
