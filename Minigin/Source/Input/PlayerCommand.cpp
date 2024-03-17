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
	const glm::vec2 newDirection{ m_MoveComp->GetDirection() + m_Direction };
	m_MoveComp->SetDirection(glm::normalize(newDirection));
}
