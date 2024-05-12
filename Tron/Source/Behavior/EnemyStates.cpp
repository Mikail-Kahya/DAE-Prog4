#include "EnemyStates.h"

#include <iostream>
#include <SceneManager.h>

using namespace mk;

void Patrolling::Update()
{
	IState::Update();
	m_Timer += Time().deltaTime;
}

std::unique_ptr<IState> Patrolling::TransitionState()
{
	//std::cout << "Patrolling\n";
	if(m_Timer > 2)
	{
		return std::make_unique<TargetPlayer>();
	}
	return {};
}

std::unique_ptr<IState> TargetPlayer::TransitionState()
{
	//std::cout << "Agro\n";
	return {};
}
