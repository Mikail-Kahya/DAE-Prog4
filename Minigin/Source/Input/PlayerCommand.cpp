#include "PlayerCommand.h"

#include "GameObject.h"

mk::MoveUpCommand::MoveUpCommand(GameObject* gameObject)
	: GameObjectCommand(gameObject) {}

void mk::MoveUpCommand::Execute()
{
	GetGameObject().AddLocalOffset(10.f, 0, 0);
}
