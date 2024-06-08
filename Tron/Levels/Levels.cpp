#include "Levels.h"

#include <fstream>
#include <iostream>
#include <SDL_image.h>

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
#include "Components/DeathComponent.h"

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

constexpr float TILE_SIZE{ 16 };

GameObject* LoadPlayer(Scene& scene, const std::string& name, const glm::vec2& startPos);
GameObject* LoadTank(Scene& scene, const std::string& tankColor, const std::string& name);
GameObject* LoadEnemy(Scene& scene, const glm::vec2& pos);
void LoadHud(Scene& scene, const std::vector<GameObject*>& players);
void LoadInfo(Scene& scene);
void LoadLevel(Scene& scene);
void LoadTile(Scene& scene, float width, float height, const glm::vec2& bottomLeft);

void mk::LoadMainGame(Scene& scene)
{
	const Renderer& renderer{ Renderer::GetInstance() };
	const int screenHeight{ renderer.GetHeight() };

	LoadLevel(scene);
	LoadInfo(scene);

	GameObject* fps = scene.SpawnObject("fps");
	fps->SetLocalPosition({ 0, 0.95f * screenHeight });
	auto fpsComponent = fps->AddComponent<FPSComponent>();
	fpsComponent->SetUpdateDelay(0.5f);

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

void LoadTile(Scene& scene, float width, float height, const glm::vec2& bottomLeft)
{
	const glm::vec2 halfSize{ width * 0.5f, height * 0.5f };

	GameObject* obstacle = scene.SpawnObject("");
	obstacle->SetLocalDepth(-10.f);
	obstacle->SetLocalPosition(bottomLeft + halfSize);
	obstacle->SetStatic(true);

	RenderComponent* spriteCompPtr = obstacle->AddComponent<RenderComponent>("MapBackground.png");
	spriteCompPtr->SetWidth(width);
	spriteCompPtr->SetHeight(height);
	spriteCompPtr->SetAnchor({ 0.5f, 0.5f });
	spriteCompPtr->SetSrcPosition(bottomLeft);
	spriteCompPtr->SetSrcSize(glm::vec2{ width, height });

	BoxColliderComponent* colliderPtr = obstacle->AddComponent<BoxColliderComponent>();
	colliderPtr->SetExtent(halfSize);
}

void LoadLevel(Scene& scene)
{
	SDL_Surface* surfacePtr = IMG_Load("./Data/Level00.png");
	uint8_t* pixels = static_cast<uint8_t*>(surfacePtr->pixels);


	std::vector<glm::vec2> playerSpawns{};
	std::vector<GameObject*> enemies{};
	for (int row{}; row < surfacePtr->h; ++row)
	{
		for (int col{}; col < surfacePtr->w; ++col) 
		{
			// surface height - row to read from bottom to top
			const int pixelIdx{ ((surfacePtr->h - row - 1) * surfacePtr->w + col) * surfacePtr->format->BytesPerPixel };
			uint8_t r = pixels[pixelIdx];
			uint8_t g = pixels[pixelIdx + 1];
			uint8_t b = pixels[pixelIdx + 2];

			const glm::vec2 pos{ col * TILE_SIZE, row * TILE_SIZE };

			if (g == 255)
				LoadTile(scene, TILE_SIZE, TILE_SIZE, pos);
			if (r == 255)
				enemies.emplace_back(LoadEnemy(scene, pos));
			if (b == 255)
				playerSpawns.emplace_back(pos + glm::vec2{ TILE_SIZE });
		}
	}
	SDL_FreeSurface(surfacePtr);

	LoadPlayer(scene, "Player1", playerSpawns[rand() % playerSpawns.size()]);
}

GameObject* LoadTank(Scene& scene, const std::string& tankColor, const std::string& name)
{
	// Tank
	GameObject* tank = scene.SpawnObject(name);

	RenderComponent* spriteCompPtr = tank->AddComponent<RenderComponent>(tankColor + "Tank.png");
	spriteCompPtr->SetAnchor({ 0.5f,0.5f });
	spriteCompPtr->SetWidth(TILE_SIZE * 2);
	spriteCompPtr->SetHeight(TILE_SIZE * 2);

	constexpr glm::vec2 tankSize{ TILE_SIZE * 0.7f };

	tank->AddComponent<MovementComponent>(50.f, 10.f, 50.f, 50.f);

	BoxColliderComponent* colliderCompPtr = tank->AddComponent<BoxColliderComponent>();
	colliderCompPtr->SetCollision({ CollisionType::block, CollisionType::overlap });
	colliderCompPtr->SetExtent(tankSize);

	// Gun
	GameObject* gun = scene.SpawnObject(name + "Gun");
	gun->SetParent(tank);

	spriteCompPtr = gun->AddComponent<RenderComponent>(tankColor + "TankGun.png");
	spriteCompPtr->SetAnchor({ 0.5f,0.5f });
	gun->AddComponent<FireComponent>(20.f);

	tank->AddComponent<HealthComponent>(3, 3);

	return tank;
}

GameObject* LoadEnemy(Scene& scene, const glm::vec2& pos)
{
	GameObject* enemyPtr{ LoadTank(scene, "Blue", "Enemy") };
	enemyPtr->SetLocalPosition(pos + glm::vec2{ TILE_SIZE });

	BoxColliderComponent* colliderPtr{ enemyPtr->GetComponent<BoxColliderComponent>() };

	enemyPtr->AddComponent<MovementComponent>();
	colliderPtr->AddObserver(enemyPtr->AddComponent<SensorComponent>());

	StateComponent* statePtr = enemyPtr->AddComponent<StateComponent>("patrolling", std::make_unique<Patrolling>());
	statePtr->AddState("targetPlayer", std::make_unique<TargetPlayer>());
	statePtr->AddState("rotate", std::make_unique<Rotate>(90.f));
	statePtr->AddState("moveBack", std::make_unique<MoveBackFromWall>());

	HealthComponent* healthCompPtr = enemyPtr->GetComponent<HealthComponent>();
	healthCompPtr->AddObserver(enemyPtr->AddComponent<DeathComponent>());

	return enemyPtr;
}
