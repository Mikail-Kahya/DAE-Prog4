#include "StateComponent.h"

using namespace mk;

StateComponent::StateComponent(std::unique_ptr<IState>&& startState)
	: m_CurrentState{ std::move(startState) }
{
}

void StateComponent::FixedUpdate()
{
	IComponent::FixedUpdate();
	m_CurrentState->FixedUpdate();
}

void StateComponent::Update()
{
	IComponent::Update();
	m_CurrentState->FixedUpdate();
}

void StateComponent::LateUpdate()
{
	IComponent::LateUpdate();
	m_CurrentState->LateUpdate();
	if (std::unique_ptr<IState> newState{ m_CurrentState->TransitionState() })
		m_CurrentState = std::move(newState);
}