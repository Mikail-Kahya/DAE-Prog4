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
		float GetRenderDepth() const;
		void SetTexture(Texture2D* texturePtr);

	private:
		Texture2D* m_TexturePtr{};
		float m_Depth{};
	};
}