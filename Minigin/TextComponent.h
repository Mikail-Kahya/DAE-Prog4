#pragma once
#include <string>
#include <memory>

#include "RenderComponent.h"

namespace mk
{
	class Font;
	
	class TextComponent final : public RenderComponent
	{
	public:
		TextComponent(GameObject* ownerPtr, const std::string& fontName, int size = 11);
		~TextComponent() override = default;

		TextComponent(const TextComponent& other)				= delete;
		TextComponent(TextComponent&& other)					= delete;
		TextComponent& operator=(const TextComponent& other)	= delete;
		TextComponent& operator=(TextComponent&& other)			= delete;

		void Update() override;

		void SetText(const std::string& text);
		void SetFont(const std::string& fontPath, unsigned int size);

		Texture2D* GetTexture() const override;

	private:
		bool m_NeedsUpdate{ false };
		std::string m_Text{};
		Font* m_FontPtr{};
		std::unique_ptr<Texture2D> m_TexturePtr{};
	};
}
