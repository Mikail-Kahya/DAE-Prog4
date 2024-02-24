#pragma once

#include "Component.h"

namespace mk
{
	class TextComponent;

	class FPSComponent : public Component
	{
	public:
		FPSComponent(GameObject* ownerPtr);
		~FPSComponent() override = default;

		FPSComponent(const FPSComponent& other)				= delete;
		FPSComponent(FPSComponent&& other)					= delete;
		FPSComponent& operator=(const FPSComponent& other)	= delete;
		FPSComponent& operator=(FPSComponent&& other)		= delete;

		void Update() override;

		void SetPrecision(int precision);
		void SetUpdateDelay(float updateDelay);

	private:

		TextComponent* m_TextCompPtr{};

		bool m_NeedsUpdate{ true };
		int m_Precision{ 1 };
		float m_UpdateDelay{ 0.5f };
		float m_Timer{};
	};
}