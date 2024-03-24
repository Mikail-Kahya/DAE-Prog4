#include "FireComponent.h"

#include "BoxColliderComponent.h"
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
	const glm::vec3 pos{ GetOwner().GetWorldPosition() };
	const glm::vec3 forward{ GetOwner().GetForward() };
	constexpr float speed{ 100.f };

	GameObject* bulletPtr{ SceneManager::GetInstance().GetScene().SpawnObject("Bullet") };
	bulletPtr->SetLocalPosition(pos + forward * m_BarrelLength);

	MovementComponent* moveCompPtr{ bulletPtr->AddComponent<MovementComponent>(speed, 0.f, speed, 0.f, false) };
	moveCompPtr->SetDirection({ forward.x, forward.y });

	RenderComponent* spriteCompPtr{ bulletPtr->AddComponent<RenderComponent>("BulletPlayer.png") };
	spriteCompPtr->SetAnchor({ 0.5f, 0.5f });

	BoxColliderComponent* colliderCompPtr{ bulletPtr->AddComponent<BoxColliderComponent>() };
	colliderCompPtr->SetExtent({ spriteCompPtr->GetTexture()->GetSize() , 0.f });
}