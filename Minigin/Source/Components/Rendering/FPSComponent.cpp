#include "FPSComponent.h"

std::unique_ptr<Component> mk::FPSComponent::Clone()
{
	return std::make_unique<FPSComponent>();
}
