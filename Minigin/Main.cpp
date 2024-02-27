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
#include "TextComponent.h"
#include "RenderComponent.h"

namespace fs = std::filesystem;
using namespace mk;

void load()
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	RenderComponent* spriteCompPtr{};

	auto gameObject = std::make_shared<GameObject>();
	scene.Add(gameObject);
	spriteCompPtr = gameObject->AddComponent<RenderComponent>("background.tga");
	
	gameObject = std::make_shared<GameObject>();
	gameObject->SetPosition(100, 100);
	scene.Add(gameObject);
	spriteCompPtr = gameObject->AddComponent<RenderComponent>("logo.tga");
	
	gameObject = std::make_shared<GameObject>();
	gameObject->SetPosition(100, 20);
	scene.Add(gameObject);
	auto testTextComponent = gameObject->AddComponent<TextComponent>("Programming 4 assignment", std::string{"Lingua.otf"}, 36);
	testTextComponent->SetText("Programming 4 assignment");

	gameObject = std::make_shared<GameObject>();
	gameObject->SetPosition(0, 20);
	scene.Add(gameObject);
	auto fpsComponent = gameObject->AddComponent<FPSComponent>();
	fpsComponent->SetUpdateDelay(0.5f);

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