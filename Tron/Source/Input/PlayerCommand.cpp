#include "PlayerCommand.h"

#include "GameObject.h"
#include "MovementComponent.h"
#include "FireComponent.h"
#include "SceneManager.h"
#include "ServiceLocator.h"

using namespace mk;

MoveCommand::MoveCommand(GameObject* gameObject, const glm::vec2& direction)
	: GameObjectCommand(gameObject)
	, m_Direction{ direction }
{
	m_MoveCompPtr = gameObject->AddComponent<MovementComponent>();
}

void MoveCommand::Execute()
{
	m_MoveCompPtr->SetDirection(m_MoveCompPtr->GetDirection() + m_Direction);
}

FireCommand::FireCommand(GameObject* gameObject)
	: GameObjectCommand(gameObject)
{
	m_FireCompPtr = gameObject->GetComponent<FireComponent>();
}

void FireCommand::Execute()
{
	m_FireCompPtr->Fire();
	ISoundSystem& sound{ ServiceLocator::GetSoundSystem() };
	sound.Play("Shoot.mp3", 1);
}

RotateCommand::RotateCommand(GameObject* gameObject, float rotateSpeed, int direction)
	: GameObjectCommand(gameObject)
	, m_RotateSpeed{ rotateSpeed }
	, m_Direction{ direction }
{
}

void RotateCommand::Execute()
{
	GetGameObject().AddRotation(m_Direction * m_RotateSpeed * Time().deltaTime);
}
