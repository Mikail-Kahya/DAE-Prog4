#pragma once
#include <string>
#include <memory>

#include "RenderComponent.h"

namespace mk
{
	class Font;
	
	class TextComponent : public RenderComponent
	{
	public:
		TextComponent() = default;
		~TextComponent() override = default;

		TextComponent(const TextComponent& other)				= delete;
		TextComponent(TextComponent&& other)					= delete;
		TextComponent& operator=(const TextComponent& other)	= delete;
		TextComponent& operator=(TextComponent&& other)			= delete;

		void Update() override;

		void SetText(const std::string& text);
		void SetFont(const std::string& fontPath, unsigned int size);

		Texture2D* GetTexture() const override;

		std::unique_ptr<Component> Clone() override;

	protected:
		bool m_NeedsUpdate{ false };

	private:
		std::string m_Text{};
		Font* m_FontPtr{};
		std::unique_ptr<Texture2D> m_TexturePtr{};
	};
}