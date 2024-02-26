#include <SDL.h>

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
#include <filesystem>

#include "FPSComponent.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "SpriteComponent.h"
#include "Scene.h"

namespace fs = std::filesystem;
using namespace mk;

void load()
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	SpriteComponent* spriteCompPtr{};

	auto go = std::make_shared<GameObject>();
	scene.Add(go);
	spriteCompPtr = go->AddComponent<SpriteComponent>("background.tga");
	
	go = std::make_shared<GameObject>();
	go->SetPosition(100, 100);
	scene.Add(go);
	spriteCompPtr = go->AddComponent<SpriteComponent>("logo.tga");
	
	go = std::make_shared<GameObject>();
	go->SetPosition(100, 20);
	scene.Add(go);
	auto testTextComponent = go->AddComponent<TextComponent>("Programming 4 assignment", std::string{"Lingua.otf"}, 36);
	testTextComponent->SetText("Programming 4 assignment");

	go = std::make_shared<GameObject>();
	go->SetPosition(0, 20);
	scene.Add(go);
	auto fpsComponent = go->AddComponent<FPSComponent>();
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