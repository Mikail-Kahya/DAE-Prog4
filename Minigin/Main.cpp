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

#include "PlayerCommand.h"
#include "Renderer.h"


namespace fs = std::filesystem;
using namespace mk;

void LoadPlayer(Scene& scene, const std::string& name);

void load()
{
	auto& scene = SceneManager::GetInstance().LoadScene("Demo");
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
	//ScoreComponent* scoreCompPtr{};

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
	tank->SetLocalPosition(200, 200);

	RenderComponent* spriteCompPtr = tank->AddComponent<RenderComponent>("BlueTank.png");
	spriteCompPtr->SetAnchor({ 0.5f,0.5f });
	tank->AddComponent<MovementComponent>(50.f, 10.f, 50.f, 50.f);
	tank->AddComponent<BoxColliderComponent>();
	//scoreCompPtr = tank1->AddComponent<ScoreComponent>();

	// Gun
	GameObject* gun = scene.SpawnObject(name + "Gun");
	gun->SetParent(tank);

	spriteCompPtr = gun->AddComponent<RenderComponent>("BlueTankGun.png");
	spriteCompPtr->SetAnchor({ 0.5f,0.f });
	gun->AddComponent<FireComponent>(glm::vec3{ 20.f, 20.f, 1.f });

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