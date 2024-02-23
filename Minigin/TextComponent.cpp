#include <stdexcept>
#include <SDL_ttf.h>
#include "TextComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "ResourceManager.h"
#include "Texture2D.h"

using namespace dae;

void TextComponent::Update()
{
	if (m_NeedsUpdate)
	{
		const SDL_Color color = { 255,255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_FontPtr->GetFont(), m_Text.c_str(), color);
		if (surf == nullptr) 
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr) 
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_TexturePtr = std::make_unique<Texture2D>(texture);
		m_NeedsUpdate = false;
	}
}

void TextComponent::Render() const
{
	if (m_TexturePtr != nullptr)
	{
		const auto& pos = m_Transform.GetPosition();
		Renderer::GetInstance().RenderTexture(*m_TexturePtr, pos.x, pos.y);
	}
}

// This implementation uses the "dirty flag" pattern
void TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void TextComponent::SetFont(const std::string& fontPath, unsigned int size)
{
	m_FontPtr = ResourceManager::GetInstance().LoadFont(fontPath, size);
}

void TextComponent::SetPosition(const float x, const float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}

Component* TextComponent::Clone()
{
	return nullptr;
}


