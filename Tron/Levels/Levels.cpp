#include "Levels.h"

#include "MkUltra.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "Renderer.h"

#include "GameObject.h"
#include "InputManager.h"

#include "TextComponent.h"
#include "RenderComponent.h"
#include "BoxColliderComponent.h"
#include "StateComponent.h"

#include "Behavior/EnemyStates.h"

#include "Components/MovementComponent.h"
#include "Components/ScoreComponent.h"
#include "Components/FireComponent.h"	
#include "Components/HealthBarComponent.h"
#include "Components/HealthComponent.h"
#include "Components/RespawnComponent.h"
#include "Components/SensorComponent.h"
#include "Components/FPSComponent.h"

#include "Input/PlayerCommand.h"


using namespace mk;

GameObject* LoadPlayer(Scene& scene, const std::string& name, const glm::vec2& startPos);
GameObject* LoadTank(Scene& scene, const std::string& tankColor, const std::string& name);
GameObject* LoadEnemy(Scene& scene);
void LoadHud(Scene& scene, const std::vector<GameObject*>& players);
void LoadInfo(Scene& scene);
void LoadLevel(Scene& scene, int screenWidth, int screenHeight);
void LoadWall(Scene& scene, const glm::vec2& position, const glm::vec2& boxExtent);

void mk::LoadMainGame(Scene& scene)
{
	const Renderer& renderer{ Renderer::GetInstance() };
	const int screenWidth{ renderer.GetWidth() };
	const int screenHeight{ renderer.GetHeight() };


	GameObject* fps = scene.SpawnObject("fps");
	fps->SetLocalPosition({ 0, 0.95f * screenHeight });
	auto fpsComponent = fps->AddComponent<FPSComponent>();
	fpsComponent->SetUpdateDelay(0.5f);

	const std::vector players{
		LoadPlayer(scene, "Player1", { 100.f, 100.f }),
		LoadPlayer(scene, "Player2", {  -100.f + screenWidth, 100.f })
	};
	//players[1]->SetStatic(true);
	LoadHud(scene, players);
	LoadInfo(scene);
	LoadEnemy(scene);
	LoadLevel(scene, screenWidth, screenHeight);
}

GameObject* LoadPlayer(Scene& scene, const std::string& name, const glm::vec2& startPos)
{
	InputManager& inputManager{ InputManager::GetInstance() };

	// controls
	Action up{};
	up.SetControllerInput(Input::dPadUp);
	up.SetKeyboardInput(SDL_SCANCODE_W);
	up.SetType(ActionType::hold);

	Action down{};
	down.SetControllerInput(Input::dPadDown);
	down.SetKeyboardInput(SDL_SCANCODE_S);
	down.SetType(ActionType::hold);

	Action left{};
	left.SetControllerInput(Input::dPadLeft);
	left.SetKeyboardInput(SDL_SCANCODE_A);
	left.SetType(ActionType::hold);

	Action right{};
	right.SetControllerInput(Input::dPadRight);
	right.SetKeyboardInput(SDL_SCANCODE_D);
	right.SetType(ActionType::hold);

	Action fire{};
	fire.SetControllerInput(Input::x);
	fire.SetKeyboardInput(SDL_SCANCODE_SPACE);
	fire.SetType(ActionType::down);

	Action rotateLeft{};
	rotateLeft.SetControllerInput(Input::bumperRight);
	rotateLeft.SetKeyboardInput(SDL_SCANCODE_Q);
	rotateLeft.SetType(ActionType::hold);

	Action rotateRight{};
	rotateRight.SetControllerInput(Input::bumperLeft);
	rotateRight.SetKeyboardInput(SDL_SCANCODE_E);
	rotateRight.SetType(ActionType::hold);

	GameObject* tankPtr = LoadTank(scene, "Red", name);
	tankPtr->SetLocalPosition(startPos);

	HealthComponent* healthCompPtr = tankPtr->AddComponent<HealthComponent>(3, 3);
	RespawnComponent* respawnCompPtr = tankPtr->AddComponent<RespawnComponent>(startPos);
	healthCompPtr->AddObserver(respawnCompPtr);

	GameObject* gunPtr{ tankPtr->GetChildWithName(name + "Gun") };

	// input
	InputMapping map{};
	auto controller = inputManager.AddController();
	map.AddMapping(up, inputManager.AddCommand<MoveCommand>(tankPtr, glm::vec2{ 0, 1 }));
	map.AddMapping(down, inputManager.AddCommand<MoveCommand>(tankPtr, glm::vec2{ 0, -1 }));
	map.AddMapping(right, inputManager.AddCommand<MoveCommand>(tankPtr, glm::vec2{ 1, 0 }));
	map.AddMapping(left, inputManager.AddCommand<MoveCommand>(tankPtr, glm::vec2{ -1, 0 }));


	constexpr float rotateSpeed{ 50.f };
	map.AddMapping(fire, inputManager.AddCommand<FireCommand>(gunPtr));
	map.AddMapping(rotateLeft, inputManager.AddCommand<RotateCommand>(gunPtr, rotateSpeed, 1));
	map.AddMapping(rotateRight, inputManager.AddCommand<RotateCommand>(gunPtr, rotateSpeed, -1));
	controller->SetInputMapping(std::move(map));

	return tankPtr;
}

void LoadHud(Scene& scene, const std::vector<GameObject*>& players)
{
	for (size_t idx{}; idx < players.size(); ++idx)
	{
		GameObject* playerPtr{ players[idx] };

		HealthComponent* healthCompPtr{ playerPtr->GetComponent<HealthComponent>() };

		GameObject* HUDWrapper{ scene.SpawnObject("Hud wrapper") };
		HUDWrapper->SetLocalPosition({ playerPtr->GetWorldPosition().x , 200 });

		GameObject* score{ scene.SpawnObject("score") };
		score->SetParent(HUDWrapper);
		TextComponent* textCompPtr{ score->AddComponent<TextComponent>("Score: 0", "Lingua.otf", 30) };
		textCompPtr->SetAnchor({ 0.5f, 0.5f });
		ScoreComponent* scoreCompPtr{ score->AddComponent<ScoreComponent>() };

		GameObject* health{ scene.SpawnObject("health") };
		health->SetParent(HUDWrapper);
		health->SetLocalPosition({ 0, 30 });
		textCompPtr = health->AddComponent<TextComponent>("Health: " + std::to_string(healthCompPtr->GetHealth()), "Lingua.otf", 20);
		textCompPtr->SetAnchor({ 0.5f, 0.5f });
		HealthBarComponent* healthBarCompPtr{ health->AddComponent<HealthBarComponent>() };

		players[(idx + 1) % players.size()]->GetComponent<HealthComponent>()->AddObserver(scoreCompPtr);
		healthCompPtr->AddObserver(healthBarCompPtr);
	}
}

void LoadInfo(Scene& scene)
{
	const float screenCenter{ 0.5f * Renderer::GetInstance().GetWidth() };

	GameObject* controlsKeyboardText{ scene.SpawnObject("FireText") };
	controlsKeyboardText->SetLocalPosition({ screenCenter , 370.f });
	controlsKeyboardText->AddComponent<TextComponent>("Use WASD to move, SPACE to fire, Q and E to turn cannon", "Lingua.otf", 20)->SetAnchor({ 0.5f,0.5f });

	GameObject* padKeyboardText{ scene.SpawnObject("FireText") };
	padKeyboardText->SetLocalPosition({ screenCenter, 400.f });
	padKeyboardText->AddComponent<TextComponent>("Use D-PAD to move, RIGHT BUMPER to fire, X and B to turn cannon", "Lingua.otf", 20)->SetAnchor({ 0.5f,0.5f });
}

void LoadLevel(Scene& scene, int screenWidth, int screenHeight)
{
	GameObject* bg = scene.SpawnObject("background");
	bg->SetStatic(true);
	bg->SetLocalDepth(-10.f);
	RenderComponent* spriteCompPtr = bg->AddComponent<RenderComponent>("level.png");
	spriteCompPtr->SetWidth(static_cast<float>(screenWidth));
	spriteCompPtr->SetHeight(static_cast<float>(screenHeight));
	//spritePtr->SetAnchor({ 0.5f, 0.5f });

}

void LoadWall(Scene& scene, const glm::vec2& position, const glm::vec2& boxExtent)
{
	GameObject* obstacle = scene.SpawnObject("");
	obstacle->SetLocalPosition(position);
	obstacle->SetStatic(true);

	BoxColliderComponent* colliderPtr = obstacle->AddComponent<BoxColliderComponent>();
	colliderPtr->SetExtent(boxExtent);

}

GameObject* LoadTank(Scene& scene, const std::string& tankColor, const std::string& name)
{
	// Tank
	GameObject* tank = scene.SpawnObject(name);

	RenderComponent* spriteCompPtr = tank->AddComponent<RenderComponent>(tankColor + "Tank.png");
	spriteCompPtr->SetAnchor({ 0.5f,0.5f });
	tank->AddComponent<MovementComponent>(50.f, 10.f, 50.f, 50.f);
	tank->AddComponent<BoxColliderComponent>()->SetCollision({ CollisionType::block, CollisionType::overlap });

	// Gun
	GameObject* gun = scene.SpawnObject(name + "Gun");
	gun->SetParent(tank);

	spriteCompPtr = gun->AddComponent<RenderComponent>(tankColor + "TankGun.png");
	spriteCompPtr->SetAnchor({ 0.5f,0.5f });
	gun->AddComponent<FireComponent>(20.f);

	return tank;
}

GameObject* LoadEnemy(Scene& scene)
{
	GameObject* enemyPtr{ LoadTank(scene, "Blue", "Enemy") };
	enemyPtr->SetLocalPosition({ 100, 300 });

	BoxColliderComponent* colliderPtr{ enemyPtr->GetComponent<BoxColliderComponent>() };

	enemyPtr->AddComponent<MovementComponent>();
	colliderPtr->AddObserver(enemyPtr->AddComponent<SensorComponent>());

	StateComponent* statePtr = enemyPtr->AddComponent<StateComponent>("patrolling", std::make_unique<Patrolling>());
	statePtr->AddState("targetPlayer", std::make_unique<TargetPlayer>());
	statePtr->AddState("rotate", std::make_unique<Rotate>(90.f));
	statePtr->AddState("moveBack", std::make_unique<MoveBackFromWall>());
	return enemyPtr;
}
