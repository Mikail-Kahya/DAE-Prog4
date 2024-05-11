#pragma once
#include <string>

#include "IComponent.h"

namespace mk
{
	class RenderComponent;
	class Texture2D;

	// Will transform to animated
	class SpriteComponent final : public IComponent
	{
	public:
		~SpriteComponent() override = default;

		SpriteComponent(const SpriteComponent& other) = delete;
		SpriteComponent(SpriteComponent&& other) = delete;
		SpriteComponent& operator=(const SpriteComponent& other) = delete;
		SpriteComponent& operator=(SpriteComponent&& other) = delete;

		void Start() override;

		void SetTexture(const std::string& file);

	private:
		SpriteComponent(const std::string& file);
		Texture2D* m_TexturePtr{};
		RenderComponent* m_RendererPtr{};
	};
}
