#include "FireComponent.h"

#include "BoxColliderComponent.h"
#include "ExplosionComponent.h"
#include "GameObject.h"

#include "SceneManager.h"

#include "MovementComponent.h"
#include "RenderComponent.h"
#include "Texture2D.h"

using namespace mk;

FireComponent::FireComponent(float barrelLength)
	: m_BarrelLength{ barrelLength }
{
}

void FireComponent::Fire() const
{
	const glm::vec2 pos{ GetOwner()->GetWorldPosition() };
	const glm::vec2 forward{ GetOwner()->GetForward() };
	constexpr float speed{ 100.f };

	GameObject* bulletPtr{ SceneManager::GetInstance().GetScene().SpawnObject("Bullet") };
	bulletPtr->SetLocalPosition(pos + forward * m_BarrelLength);

	MovementComponent* moveCompPtr{ bulletPtr->AddComponent<MovementComponent>(speed, 0.f, speed, 0.f, false) };
	moveCompPtr->SetDirection(forward);

	RenderComponent* spriteCompPtr{ bulletPtr->AddComponent<RenderComponent>("BulletPlayer.png") };
	spriteCompPtr->SetAnchor({ 0.5f, 0.5f });

	BoxColliderComponent* colliderCompPtr{ bulletPtr->AddComponent<BoxColliderComponent>() };
	colliderCompPtr->SetExtent({ spriteCompPtr->GetTexture()->GetSize()  });
	colliderCompPtr->Ignore(GetOwner());
	colliderCompPtr->Ignore(GetOwner()->GetParent());

	colliderCompPtr->AddObserver(bulletPtr->AddComponent<ExplosionComponent>());
}