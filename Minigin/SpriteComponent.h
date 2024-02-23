#pragma once
#include <string>

#include "RenderComponent.h"

namespace mk
{
	class SpriteComponent : public RenderComponent
	{
	public:
		SpriteComponent() = default;
		~SpriteComponent() override = default;

		SpriteComponent(const SpriteComponent& other) = delete;
		SpriteComponent(SpriteComponent&& other) = delete;
		SpriteComponent& operator=(const SpriteComponent& other) = delete;
		SpriteComponent& operator=(SpriteComponent&& other) = delete;

		void SetTexture(const std::string& file);

		Texture2D* GetTexture() const override;

		std::unique_ptr<Component> Clone() override { return std::make_unique<SpriteComponent>(); }

	private:
		Texture2D* m_TexturePtr{};
	};
}