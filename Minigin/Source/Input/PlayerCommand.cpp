#include "PlayerCommand.h"

#include "GameObject.h"
#include "MovementComponent.h"

using namespace mk;

MoveCommand::MoveCommand(GameObject* gameObject, const glm::vec2& direction)
	: GameObjectCommand(gameObject)
	, m_Direction{ direction }
{
	m_MoveComp = gameObject->AddComponent<MovementComponent>();
}

void MoveCommand::Execute()
{
	m_MoveComp->SetDirection(m_MoveComp->GetDirection() + m_Direction);
}
