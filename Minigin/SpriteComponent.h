#pragma once
#include <string>

#include "Component.h"

namespace mk
{
	class RenderComponent;
	class Texture2D;

	class SpriteComponent final : public Component
	{
	public:
		SpriteComponent(const std::string& file);
		~SpriteComponent() override = default;

		SpriteComponent(const SpriteComponent& other) = delete;
		SpriteComponent(SpriteComponent&& other) = delete;
		SpriteComponent& operator=(const SpriteComponent& other) = delete;
		SpriteComponent& operator=(SpriteComponent&& other) = delete;

		void Start() override;

		void SetTexture(const std::string& file);

	private:
		Texture2D* m_TexturePtr{};
		RenderComponent* m_RendererPtr{};
	};
}
