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
#include "Test.h"

namespace fs = std::filesystem;
using namespace mk;

void load()
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");
	const Renderer& renderer{ Renderer::GetInstance() };
	InputManager& inputManager{ InputManager::GetInstance() };
	const int screenWidth{ renderer.GetWidth() };
	const int screenHeight{ renderer.GetHeight() };

	Controller* controller{};
	RenderComponent* spriteCompPtr{};
	MovementComponent* moveCompPtr{};
	BoxColliderComponent* boxCompPtr{};
	Test* testPtr{};

	GameObject* bg = scene.SpawnObject("bg");
	spriteCompPtr = bg->AddComponent<RenderComponent>("background.tga");
	
	GameObject* logo = scene.SpawnObject("logo");
	logo->SetLocalPosition(screenWidth * 0.5f, screenHeight * 0.5f);
	spriteCompPtr = logo->AddComponent<RenderComponent>("logo.tga");
	spriteCompPtr->SetAnchor({ 0.5f, 0.5f });
	
	GameObject* text = scene.SpawnObject("text");
	auto testTextComponent = text->AddComponent<TextComponent>("Programming 4 assignment", std::string{"Lingua.otf"}, 36);
	testTextComponent->SetText("Programming 4 assignment");
	testTextComponent->SetAnchor({ 0.5f, 0.5f });
	text->SetLocalPosition(screenWidth * 0.5f, screenHeight * 0.9f);


	GameObject* fps = scene.SpawnObject("fps");
	fps->SetLocalPosition(0, screenHeight * 0.95f);
	auto fpsComponent = fps->AddComponent<FPSComponent>();
	fpsComponent->SetUpdateDelay(0.5f);

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

	// Player 1
	GameObject* tank1 = scene.SpawnObject("Player1");
	tank1->SetLocalPosition(200, 200);
	spriteCompPtr = tank1->AddComponent<RenderComponent>("BlueTank.png");
	spriteCompPtr->SetAnchor({ 0.5f,0.5f });
	moveCompPtr = tank1->AddComponent<MovementComponent>(50.f, 10.f, 50.f, 50.f);
	boxCompPtr = tank1->AddComponent<BoxColliderComponent>();
	testPtr = tank1->AddComponent<Test>();
	boxCompPtr->AddObserver(testPtr);

	InputMapping map{};
	controller = inputManager.AddController();
	map.AddMapping(up, inputManager.AddCommand<MoveCommand>(tank1, glm::vec2{ 0, 1 }));
	map.AddMapping(down, inputManager.AddCommand<MoveCommand>(tank1, glm::vec2{ 0, -1 }));
	map.AddMapping(left, inputManager.AddCommand<MoveCommand>(tank1, glm::vec2{ -1, 0 }));
	map.AddMapping(right, inputManager.AddCommand<MoveCommand>(tank1, glm::vec2{ 1, 0 }));
	controller->SetInputMapping(std::move(map));

	// Player 2
	GameObject* tank2 = scene.SpawnObject("Player2");
	tank2->SetLocalPosition(200, 100);
	spriteCompPtr = tank2->AddComponent<RenderComponent>("BlueTank.png");
	spriteCompPtr->SetAnchor({ 0.5f,0.5f });

	controller = inputManager.AddController();
	map.AddMapping(up, inputManager.AddCommand<MoveCommand>(tank2, glm::vec2{ 0, 1 }));
	map.AddMapping(down, inputManager.AddCommand<MoveCommand>(tank2, glm::vec2{ 0, -1 }));
	map.AddMapping(left, inputManager.AddCommand<MoveCommand>(tank2, glm::vec2{ -1, 0 }));
	map.AddMapping(right, inputManager.AddCommand<MoveCommand>(tank2, glm::vec2{ 1, 0 }));
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