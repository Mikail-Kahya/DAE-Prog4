#pragma once
#include "IComponent.h"
#include "IObserver.h"

namespace mk
{
	class SensorComponent : public IComponent, public IObserver
	{
	public:
		SensorComponent() = default;
		~SensorComponent() override = default;

		SensorComponent(const SensorComponent& other)					= delete;
		SensorComponent(SensorComponent&& other) noexcept				= delete;
		SensorComponent& operator=(const SensorComponent& other)		= delete;
		SensorComponent& operator=(SensorComponent&& other)	noexcept	= delete;

		void OnNotify(ISubject* subjectPtr, IEvent* event) override;

		void FixedUpdate() override;

		bool HitWall() const;

	private:
		bool m_HitWall{};
	};
}
