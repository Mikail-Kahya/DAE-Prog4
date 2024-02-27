#include <stdexcept>
#include <SDL_ttf.h>

#include "TextComponent.h"
#include "RenderComponent.h"
#include "GameObject.h"

#include "Renderer.h"
#include "ResourceManager.h"

#include "Font.h"
#include "Texture2D.h"

using namespace mk;

TextComponent::TextComponent(const std::string& text, const std::string& fontName, int size)
	: m_Text{ text }
{
	m_FontPtr = ResourceManager::GetInstance().LoadFont(fontName, size);
}

void TextComponent::Start()
{
	m_RendererPtr = GetOwner().AddComponent<RenderComponent>(m_Texture.get());
}

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
		m_Texture = std::make_unique<Texture2D>(texture);
		m_RendererPtr->SetTexture(m_Texture.get());
		m_NeedsUpdate = false;
	}
}

void TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void TextComponent::SetFont(const std::string& fontPath, unsigned int size)
{
	Font* fontPtr{ ResourceManager::GetInstance().LoadFont(fontPath, size) };
	m_NeedsUpdate = m_FontPtr != fontPtr;
	m_FontPtr = fontPtr;
}