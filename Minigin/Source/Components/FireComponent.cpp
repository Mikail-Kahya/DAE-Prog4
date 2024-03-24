#include "FireComponent.h"

#include "GameObject.h"

#include "SceneManager.h"

#include "MovementComponent.h"
#include "RenderComponent.h"

using namespace mk;

FireComponent::FireComponent(const glm::vec3& socketOffset)
	: m_SocketOffset{ socketOffset }
{
}

void FireComponent::Fire() const
{
	const glm::vec3 pos{ GetOwner().GetWorldPosition() };
	const glm::vec3 forward{ GetOwner().GetForward() };
	constexpr float speed{ 100.f };

	GameObject* bulletPtr{ SceneManager::GetInstance().GetScene().SpawnObject("Bullet") };
	bulletPtr->SetLocalPosition(pos + m_SocketOffset);

	MovementComponent* moveCompPtr{ bulletPtr->AddComponent<MovementComponent>(speed, 0.f, speed, 0.f, false) };
	moveCompPtr->SetDirection({ forward.x, forward.y });

	RenderComponent* spriteCompPtr{ bulletPtr->AddComponent<RenderComponent>("BulletPlayer.png") };
	spriteCompPtr->SetAnchor({ 0.5f, 0.5f });
}