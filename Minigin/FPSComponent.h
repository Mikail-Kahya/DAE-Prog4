#pragma once

namespace mk
{
	class FPSComponent
	{
	public:
		FPSComponent() = default;
		~FPSComponent() = default;

		FPSComponent(const FPSComponent& other)				= delete;
		FPSComponent(FPSComponent&& other)					= delete;
		FPSComponent& operator=(const FPSComponent& other)	= delete;
		FPSComponent& operator=(FPSComponent&& other)			= delete;

	private:
	};
}