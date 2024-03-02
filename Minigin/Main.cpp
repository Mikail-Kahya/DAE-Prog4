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
#include "OrbitComponent.h"

namespace fs = std::filesystem;
using namespace mk;

void load()
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	RenderComponent* spriteCompPtr{};

	const auto gameObject1 = scene.SpawnObject("bg");
	spriteCompPtr = gameObject1->AddComponent<RenderComponent>("background.tga");
	gameObject1->SetLocalPosition(0, 0);
	
	const auto gameObject2 = scene.SpawnObject("logo");
	gameObject2->SetLocalPosition(100, 100);
	spriteCompPtr = gameObject2->AddComponent<RenderComponent>("logo.tga");
	
	const auto gameObject3 = scene.SpawnObject("text");
	gameObject3->SetLocalPosition(100, 100);
	auto testTextComponent = gameObject3->AddComponent<TextComponent>("Programming 4 assignment", std::string{"Lingua.otf"}, 36);
	testTextComponent->SetText("Programming 4 assignment");

	const auto gameObject4 = scene.SpawnObject("fps");
	gameObject4->SetParent(gameObject2, false);
	auto fpsComponent = gameObject4->AddComponent<FPSComponent>();
	fpsComponent->SetUpdateDelay(0.5f);
	auto movementComponent = gameObject4->AddComponent<OrbitComponent>(100.f, 5.f);
	movementComponent->SetAngle(100);
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