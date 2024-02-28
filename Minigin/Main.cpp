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

	auto gameObject1 = std::make_shared<GameObject>("1");
	scene.Add(gameObject1);
	spriteCompPtr = gameObject1->AddComponent<RenderComponent>("background.tga");
	
	auto gameObject2 = std::make_shared<GameObject>("2");
	gameObject2->SetPosition(100, 100);
	scene.Add(gameObject2);
	spriteCompPtr = gameObject2->AddComponent<RenderComponent>("logo.tga");
	
	auto gameObject3 = std::make_shared<GameObject>("3");
	gameObject3->SetPosition(100, 100);
	scene.Add(gameObject3);
	auto testTextComponent = gameObject3->AddComponent<TextComponent>("Programming 4 assignment", std::string{"Lingua.otf"}, 36);
	testTextComponent->SetText("Programming 4 assignment");

	auto gameObject4 = std::make_shared<GameObject>("4");
	gameObject4->SetPosition(0, 20);
	scene.Add(gameObject4);
	auto fpsComponent = gameObject4->AddComponent<FPSComponent>();
	fpsComponent->SetUpdateDelay(0.5f);

	gameObject3->SetParent(gameObject2.get(), false);
	gameObject2->Destroy();
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