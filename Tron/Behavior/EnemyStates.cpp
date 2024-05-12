#include "EnemyStates.h"

#include <iostream>
#include <SceneManager.h>
#include "Components/MovementComponent.h"
#include "Components/SensorComponent.h"

using namespace mk;

void Patrolling::Start()
{
	GameObjectState::Start();
	m_MovementPtr = GetOwner()->GetComponent<MovementComponent>();
	m_SensorPtr = GetOwner()->GetComponent<SensorComponent>();
}

void Patrolling::Update()
{
	IState::Update();
	m_MovementPtr->SetDirection(GetOwner()->GetForward());
	m_Timer += Time().deltaTime;
}

std::string Patrolling::TransitionState()
{
	//std::cout << "Patrolling\n";
	if(m_SensorPtr->HitWall())
		return "moveBack";
	return {};
}


void MoveBackFromWall::Start()
{
	GameObjectState::Start();
	m_MovementPtr = GetOwner()->GetComponent<MovementComponent>();
}

void MoveBackFromWall::Update()
{
	GameObjectState::Update();
	m_MovementPtr->SetDirection(-GetOwner()->GetForward());
	m_Timer += Time().deltaTime;
}

std::string MoveBackFromWall::TransitionState()
{
	if (m_Timer > m_MoveTime)
		return "rotate";
	return {};
}

Rotate::Rotate(float rotationSpeed)
	: m_RotationSpeed{ rotationSpeed }
{
}

void Rotate::OnEnter()
{
	GameObjectState::OnEnter();
	m_Rotation = 0;
}

void Rotate::OnExit()
{
	GameObjectState::OnExit();
	GetOwner()->SetRotation(std::fmod(GetOwner()->GetRotation(), 360.f));
}

void Rotate::Update()
{
	GameObjectState::Update();
	const float deltaRot{ Time().deltaTime * m_RotationSpeed };
	m_Rotation += deltaRot;
	GetOwner()->AddRotation(deltaRot);
}

std::string Rotate::TransitionState()
{
	if (m_Rotation > 90)
		return "patrolling";
	return {};
}

std::string TargetPlayer::TransitionState()
{
	//std::cout << "Agro\n";
	return {};
}
