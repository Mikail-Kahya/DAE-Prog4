#pragma once
#include <string>
#include <memory>
#include "GameObject.h"
#include "Transform.h"

namespace dae
{
	class Font;
	class Texture2D;
	class TextObject final
	{
	public:
		TextObject(const std::string& text, Font* fontPtr);
		virtual ~TextObject() = default;

		TextObject(const TextObject& other)				= delete;
		TextObject(TextObject&& other)					= delete;
		TextObject& operator=(const TextObject& other)	= delete;
		TextObject& operator=(TextObject&& other)		= delete;

		void Update();
		void Render() const;

		void SetText(const std::string& text);
		void SetPosition(float x, float y);

	private:
		bool m_needsUpdate{ false };
		std::string m_text;
		Transform m_transform{};
		Font* m_FontPtr{};
		std::unique_ptr<Texture2D> m_TexturePtr{};
	};
}
