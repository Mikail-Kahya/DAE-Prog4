#pragma once

#include <string_view>

#include "Component.h"
#include "Transform.h"

namespace mk
{
	class Texture2D;

	class RenderComponent final : public Component
	{
	public:
		RenderComponent(Texture2D* texturePtr);
		RenderComponent(const std::string& file);
		~RenderComponent() override;

		RenderComponent(const RenderComponent& other)				= delete;
		RenderComponent(RenderComponent&& other)					= delete;
		RenderComponent& operator=(const RenderComponent& other)	= delete;
		RenderComponent& operator=(RenderComponent&& other)			= delete;

		void Start() override;

		void LateUpdate() override;

		Texture2D* GetTexture() const;
		glm::vec2 GetRenderPosition() const;
		float GetRenderDepth() const;
		std::pair<bool, bool> IsFlipped() const;
		const glm::vec2& GetAnchor() const;

		void SetTexture(Texture2D* texturePtr);
		void SetAnchor(const glm::vec2& anchor);
		void SetFlipHorizontal(bool isFlipped);
		void SetFlipVertical(bool isFlipped);

	private:
		int GetTextureWidth() const;
		int GetTextureHeight() const;

		glm::vec2 m_Anchor{};
		Texture2D* m_TexturePtr{};
		float m_Depth{};
		std::pair<bool, bool> m_FlipAxis{ false, false };
	};
}