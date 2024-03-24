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
	const float angle{ GetOwner().GetRotation() };
	constexpr float speed{ 100.f };

	GameObject* bulletPtr{ SceneManager::GetInstance().GetScene().SpawnObject("Bullet") };
	bulletPtr->SetLocalPosition(pos + m_SocketOffset);

	MovementComponent* moveCompPtr{};
	moveCompPtr = bulletPtr->AddComponent<MovementComponent>(speed, 0.f, speed, 0.f, false);
	moveCompPtr->SetDirection({ cosf(angle), sinf(angle) });

	RenderComponent* spriteCompPtr{};
	spriteCompPtr = bulletPtr->AddComponent<RenderComponent>("BulletPlayer.png");
	spriteCompPtr->SetAnchor({ 0.5f, 0.5f });
}

