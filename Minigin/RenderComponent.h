#pragma once

#include "Component.h"
#include "Transform.h"

namespace mk
{
	class Texture2D;

	class RenderComponent : public Component
	{
	public:
		~RenderComponent() override;

		RenderComponent(const RenderComponent& other)				= delete;
		RenderComponent(RenderComponent&& other)					= delete;
		RenderComponent& operator=(const RenderComponent& other)	= delete;
		RenderComponent& operator=(RenderComponent&& other)			= delete;

		void SetPosition(float x, float y, float z = 0.f);

		const Transform& GetTransform() const;
		virtual Texture2D* GetTexture() const = 0;

	protected:
		RenderComponent();

	private:
		Transform m_Transform{};
	};
}