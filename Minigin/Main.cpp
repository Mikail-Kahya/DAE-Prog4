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

#include "PlayerCommand.h"
#include "Renderer.h"
#include "ScoreComponent.h"

namespace fs = std::filesystem;
using namespace mk;

void LoadPlayer(Scene& scene, const std::string& name);

void load()
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");
	const Renderer& renderer{ Renderer::GetInstance() };
	const int screenHeight{ renderer.GetHeight() };


	GameObject* fps = scene.SpawnObject("fps");
	fps->SetLocalPosition(0, screenHeight * 0.95f);
	auto fpsComponent = fps->AddComponent<FPSComponent>();
	fpsComponent->SetUpdateDelay(0.5f);

	LoadPlayer(scene, "Player1");
	LoadPlayer(scene, "Player2");
}

void LoadPlayer(Scene& scene, const std::string& name)
{
	InputManager& inputManager{ InputManager::GetInstance() };
	MovementComponent* moveCompPtr{};
	BoxColliderComponent* boxCompPtr{};
	ScoreComponent* scoreCompPtr{};

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

	// Player 1
	GameObject* tank1 = scene.SpawnObject(name);
	tank1->SetLocalPosition(200, 200);
	auto spriteCompPtr = tank1->AddComponent<RenderComponent>("BlueTank.png");
	spriteCompPtr->SetAnchor({ 0.5f,0.5f });
	moveCompPtr = tank1->AddComponent<MovementComponent>(50.f, 10.f, 50.f, 50.f);
	boxCompPtr = tank1->AddComponent<BoxColliderComponent>();
	scoreCompPtr = tank1->AddComponent<ScoreComponent>();

	//FireCommand* commandPtr{ inputManager.AddCommand<FireCommand>() };

	InputMapping map{};
	auto controller = inputManager.AddController();
	map.AddMapping(up, inputManager.AddCommand<MoveCommand>(tank1, glm::vec2{ 0, 1 }));
	map.AddMapping(down, inputManager.AddCommand<MoveCommand>(tank1, glm::vec2{ 0, -1 }));
	map.AddMapping(left, inputManager.AddCommand<MoveCommand>(tank1, glm::vec2{ -1, 0 }));
	map.AddMapping(right, inputManager.AddCommand<MoveCommand>(tank1, glm::vec2{ 1, 0 }));

	map.AddMapping(fire, inputManager.AddCommand<FireCommand>(tank1));
	controller->SetInputMapping(std::move(map));
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