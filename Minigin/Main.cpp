#include <SDL.h>
#include <filesystem>

#ifdef WIN32
#include <windows.h>
#endif

//#if _DEBUG
//// ReSharper disable once CppUnusedIncludeDirective
//#if __has_include(<vld.h>)
//#include <vld.h>
//#endif
//#endif

#include "MkUltra.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"

#include "GameObject.h"
#include "InputManager.h"

#include "FPSComponent.h"
#include "TextComponent.h"
#include "RenderComponent.h"
#include "MovementComponent.h"
#include "BoxColliderComponent.h"
#include "ScoreComponent.h"
#include "FireComponent.h"	
#include "HealthComponent.h"

#include "PlayerCommand.h"
#include "Renderer.h"
#include "RespawnComponent.h"


namespace fs = std::filesystem;
using namespace mk;

GameObject* LoadPlayer(Scene& scene, const std::string& name, const glm::vec2& startPos);
void LoadHud(Scene& scene, const std::vector<GameObject*>& players);

void load()
{
	auto& scene = SceneManager::GetInstance().LoadScene("Demo");
	const Renderer& renderer{ Renderer::GetInstance() };
	const int screenWidth{ renderer.GetWidth() };
	const int screenHeight{ renderer.GetHeight() };


	GameObject* fps = scene.SpawnObject("fps");
	fps->SetLocalPosition(0, screenHeight * 0.95f);
	auto fpsComponent = fps->AddComponent<FPSComponent>();
	fpsComponent->SetUpdateDelay(0.5f);

	const std::vector players{
		LoadPlayer(scene, "Player1", { 100.f, 100.f }),
		LoadPlayer(scene, "Player2", { screenWidth - 100.f, 100.f })
	};
	LoadHud(scene, players);
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
	fire.SetControllerInput(Input::bumperRight);
	fire.SetKeyboardInput(SDL_SCANCODE_SPACE);
	fire.SetType(ActionType::down);

	Action rotateLeft{};
	rotateLeft.SetControllerInput(Input::x);
	rotateLeft.SetKeyboardInput(SDL_SCANCODE_Q);
	rotateLeft.SetType(ActionType::hold);

	Action rotateRight{};
	rotateRight.SetControllerInput(Input::b);
	rotateRight.SetKeyboardInput(SDL_SCANCODE_E);
	rotateRight.SetType(ActionType::hold);

	// Tank
	GameObject* tank = scene.SpawnObject(name);
	tank->SetLocalPosition(startPos.x, startPos.y);

	RenderComponent* spriteCompPtr = tank->AddComponent<RenderComponent>("BlueTank.png");
	spriteCompPtr->SetAnchor({ 0.5f,0.5f });
	tank->AddComponent<MovementComponent>(50.f, 10.f, 50.f, 50.f);
	tank->AddComponent<BoxColliderComponent>();
	HealthComponent* healthCompPtr = tank->AddComponent<HealthComponent>(3, 3);
	RespawnComponent* respawnCompPtr = tank->AddComponent<RespawnComponent>(glm::vec3{ startPos, 0.f });
	healthCompPtr->AddObserver(respawnCompPtr);

	// Gun
	GameObject* gun = scene.SpawnObject(name + "Gun");
	gun->SetParent(tank);

	spriteCompPtr = gun->AddComponent<RenderComponent>("BlueTankGun.png");
	spriteCompPtr->SetAnchor({ 0.5f,0.f });
	gun->AddComponent<FireComponent>(50.f);

	// input
	InputMapping map{};
	auto controller = inputManager.AddController();
	map.AddMapping(up, inputManager.AddCommand<MoveCommand>(tank, glm::vec2{ 0, 1 }));
	map.AddMapping(down, inputManager.AddCommand<MoveCommand>(tank, glm::vec2{ 0, -1 }));
	map.AddMapping(right, inputManager.AddCommand<MoveCommand>(tank, glm::vec2{ 1, 0 }));
	map.AddMapping(left, inputManager.AddCommand<MoveCommand>(tank, glm::vec2{ -1, 0 }));


	constexpr float rotateSpeed{ 50.f };
	map.AddMapping(fire, inputManager.AddCommand<FireCommand>(gun));
	map.AddMapping(rotateLeft, inputManager.AddCommand<RotateCommand>(gun, rotateSpeed, 1));
	map.AddMapping(rotateRight, inputManager.AddCommand<RotateCommand>(gun, rotateSpeed, -1));
	controller->SetInputMapping(std::move(map));

	return tank;
}

void LoadHud(Scene& scene, const std::vector<GameObject*>& players)
{
	GameObject* HUDWrapper{ scene.SpawnObject("Hud wrapper") };
	HUDWrapper->SetLocalPosition(20, 200);

	GameObject* score{ scene.SpawnObject("score") };
	score->SetParent(HUDWrapper);
	ScoreComponent* scoreCompPtr = score->AddComponent<ScoreComponent>();

	for (GameObject* playerPtr : players)
	{
		HealthComponent* healthCompPtr{ playerPtr->GetComponent<HealthComponent>() };
		healthCompPtr->AddObserver(scoreCompPtr);
	}
	
}


int main(int, char*[]) {

#if __EMSCRIPTEN__
	fs::path data_location = "";
#else
	fs::path data_location = "./Data/";
	if(!fs::exists(data_location))
		data_location = "../Data/";
#endif
	MkUltra engine(data_location);
	engine.Run(load);

	return 0;
}
