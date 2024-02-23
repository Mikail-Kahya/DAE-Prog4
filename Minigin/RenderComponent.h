#pragma once

#include <memory>
#include <string_view>

#include "Component.h"
#include "Transform.h"

namespace dae
{
	class Texture2D;

	class RenderComponent : public Component
	{
	public:
		virtual ~RenderComponent() override;

		RenderComponent(const RenderComponent& other)				= delete;
		RenderComponent(RenderComponent&& other)					= delete;
		RenderComponent& operator=(const RenderComponent& other)	= delete;
		RenderComponent& operator=(RenderComponent&& other)			= delete;

		void SetPosition(float x, float y);

		const Transform& GetTransform() const;
		virtual Texture2D* GetTexture() const = 0;

	protected:
		RenderComponent();

	private:
		Transform m_Transform{};
	};
}