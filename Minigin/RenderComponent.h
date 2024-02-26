#pragma once

#include "Component.h"
#include "Transform.h"

namespace mk
{
	class Texture2D;

	class RenderComponent : public Component
	{
	public:
		RenderComponent(Texture2D* texturePtr);
		~RenderComponent() override;

		RenderComponent(const RenderComponent& other)				= delete;
		RenderComponent(RenderComponent&& other)					= delete;
		RenderComponent& operator=(const RenderComponent& other)	= delete;
		RenderComponent& operator=(RenderComponent&& other)			= delete;

		const Transform& GetTransform() const;
		Texture2D* GetTexture() const;
		void SetTexture(Texture2D* texturePtr);

	private:
		Texture2D* m_TexturePtr{};
	};
}