#pragma once
#include <string>
#include <memory>

#include "Component.h"
#include "GameObject.h"
#include "Transform.h"

namespace dae
{
	class Font;
	class Texture2D;
	class TextComponent : public Component
	{
	public:
		TextComponent() = default;
		virtual ~TextComponent() override = default;

		TextComponent(const TextComponent& other)				= delete;
		TextComponent(TextComponent&& other)					= delete;
		TextComponent& operator=(const TextComponent& other)	= delete;
		TextComponent& operator=(TextComponent&& other)			= delete;

		void Update() override;
		void Render() const override;

		void SetText(const std::string& text);
		void SetFont(const std::string& fontPath, unsigned int size);
		void SetPosition(float x, float y);

		std::unique_ptr<Component> Clone() override { return std::make_unique<TextComponent>(); }

	private:
		bool m_NeedsUpdate{ false };
		std::string m_Text{};
		Transform m_Transform{};
		Font* m_FontPtr{};
		std::unique_ptr<Texture2D> m_TexturePtr{};
	};
}