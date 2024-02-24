#pragma once
#include <string>

#include "RenderComponent.h"

namespace mk
{
	class SpriteComponent final : public RenderComponent
	{
	public:
		SpriteComponent(const std::string& file);
		~SpriteComponent() override = default;

		SpriteComponent(const SpriteComponent& other) = delete;
		SpriteComponent(SpriteComponent&& other) = delete;
		SpriteComponent& operator=(const SpriteComponent& other) = delete;
		SpriteComponent& operator=(SpriteComponent&& other) = delete;

		void SetTexture(const std::string& file);

		Texture2D* GetTexture() const override;

	private:
		Texture2D* m_TexturePtr{};
	};
}