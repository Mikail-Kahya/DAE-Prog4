#pragma once

#include "TextComponent.h"

namespace mk
{
	class FPSComponent : public TextComponent
	{
	public:
		FPSComponent() = default;
		~FPSComponent() override = default;

		FPSComponent(const FPSComponent& other)				= delete;
		FPSComponent(FPSComponent&& other)					= delete;
		FPSComponent& operator=(const FPSComponent& other)	= delete;
		FPSComponent& operator=(FPSComponent&& other)		= delete;

		void Update() override;

		std::unique_ptr<Component> Clone() override;

	private:
	};
}