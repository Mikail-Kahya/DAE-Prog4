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

		void SetPrecision(int precision);
		void SetUpdateDelay(float updateDelay);

		std::unique_ptr<Component> Clone() override;

	private:
		void UpdateText();

		int m_Precision{ 1 };
		float m_UpdateDelay{ 0.5f };
		float m_Timer{};
	};
}