#pragma once
#include <string>
#include <memory>

#include "Component.h"
#include "glm/vec2.hpp"

namespace mk
{
	class RenderComponent;
	class Texture2D;
	class Font;
	
	class TextComponent final : public Component
	{
	public:
		TextComponent(const std::string& text, const std::string& fontName = "Lingua.otf", int size = 11);
		~TextComponent() override = default;

		TextComponent(const TextComponent& other)				= delete;
		TextComponent(TextComponent&& other)					= delete;
		TextComponent& operator=(const TextComponent& other)	= delete;
		TextComponent& operator=(TextComponent&& other)			= delete;

		void Start() override;

		void Update() override;

		void SetText(const std::string& text);
		void SetFont(const std::string& fontPath, unsigned int size);
		void SetAnchor(const glm::vec2& anchor);

	private:
		bool m_NeedsUpdate{ false };
		std::string m_Text{};
		Font* m_FontPtr{};
		std::unique_ptr<Texture2D> m_Texture{};
		RenderComponent* m_RendererPtr{};
	};
}
