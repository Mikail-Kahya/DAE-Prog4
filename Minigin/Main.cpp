#include <SDL.h>
#include <filesystem>

#ifdef WIN32
#include <windows.h>
#endif

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"

#include "GameObject.h"
#include "FPSComponent.h"
#include "GUI.h"
#include "InputManager.h"
#include "MeasureWidget.h"
#include "TextComponent.h"
#include "RenderComponent.h"
#include "OrbitComponent.h"
#include "PlayerCommand.h"

namespace fs = std::filesystem;
using namespace mk;

void load()
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	Controller* controller{};
	RenderComponent* spriteCompPtr{};

	GameObject* bg = scene.SpawnObject("bg");
	spriteCompPtr = bg->AddComponent<RenderComponent>("background.tga");
	
	GameObject* logo = scene.SpawnObject("logo");
	logo->SetLocalPosition(200, 100);
	spriteCompPtr = logo->AddComponent<RenderComponent>("logo.tga");
	
	GameObject* text = scene.SpawnObject("text");
	text->SetLocalPosition(80, 30);
	auto testTextComponent = text->AddComponent<TextComponent>("Programming 4 assignment", std::string{"Lingua.otf"}, 36);
	testTextComponent->SetText("Programming 4 assignment");

	GameObject* fps = scene.SpawnObject("fps");
	fps->SetLocalPosition(10, 10);
	auto fpsComponent = fps->AddComponent<FPSComponent>();
	fpsComponent->SetUpdateDelay(0.5f);

	GameObject* tankWrapper = scene.SpawnObject("tankWrapper");
	tankWrapper->SetLocalPosition(200, 200);

	GameObject* tank1 = scene.SpawnObject("Player1");
	tank1->SetParent(tankWrapper);
	spriteCompPtr = tank1->AddComponent<RenderComponent>("BlueTank.png");
	spriteCompPtr->SetAnchor({ 0.5f,0.5f });

	// controls
	controller = InputManager::GetInstance().AddController();

	Action up{};
	up.SetControllerInput(Input::dPadUp);
	up.SetKeyboardInput(SDL_SCANCODE_W);
	up.SetType(ActionType::hold);

	InputMapping mapping{};
	mapping.AddInput<MoveUpCommand>(up, tankWrapper);

	controller->SetInputMapping(std::move(mapping));

	//GameObject* tank2 = scene.SpawnObject("T2");
	//tank2->SetParent(tank1);
	//spriteCompPtr = tank2->AddComponent<RenderComponent>("BlueTank.png");
	//spriteCompPtr->SetAnchor({ 0.5f,0.5f });

	// GUI exercise week 3
	//MeasureWidget* measurer{};
	//measurer = GUI::GetInstance().Add<MeasureWidget>("Trash the cache");
	//measurer = GUI::GetInstance().Add<MeasureWidget>("Cache the trash");
}

int main(int, char*[]) {

#if __EMSCRIPTEN__
	fs::path data_location = "";
#else
	fs::path data_location = "./Data/";
	if(!fs::exists(data_location))
		data_location = "../Data/";
#endif
	Minigin engine(data_location);
	engine.Run(load);

	return 0;
}