#pragma once
#include <memory>

#include "IComponent.h"
#include "IState.h"

namespace mk
{
	class StateComponent : public IComponent
	{
	public:
		StateComponent(std::unique_ptr<IState>&& startState);
		~StateComponent() override = default;

		StateComponent(const StateComponent& other)					= delete;
		StateComponent(StateComponent&& other) noexcept				= delete;
		StateComponent& operator=(const StateComponent& other)		= delete;
		StateComponent& operator=(StateComponent&& other) noexcept	= delete;

		void FixedUpdate() override;
		void Update() override;
		void LateUpdate() override;

	private:
		std::unique_ptr<IState> m_CurrentState{};
	};
}
