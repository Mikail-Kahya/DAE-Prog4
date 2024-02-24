#include <stdexcept>
#include <sstream>
#include <iostream>
#include <thread>

#if WIN32
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#endif

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Minigin.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"

SDL_Window* g_window{};

void LogSDLVersion(const std::string& message, const SDL_version& v)
{
#if WIN32
	std::stringstream ss;
	ss << message << (int)v.major << "." << (int)v.minor << "." << (int)v.patch << "\n";
	OutputDebugString(ss.str().c_str());
#else
	std::cout << message << (int)v.major << "." << (int)v.minor << "." << (int)v.patch << "\n";
#endif
}

#ifdef __EMSCRIPTEN__
#include "emscripten.h"

void LoopCallback(void* arg)
{
	static_cast<mk::Minigin*>(arg)->RunOneFrame();
}
#endif

// Why bother with this? Because sometimes students have a different SDL version installed on their pc.
// That is not a problem unless for some reason the dll's from this project are not copied next to the exe.
// These entries in the debug output help to identify that issue.
void PrintSDLVersion()
{
	SDL_version version{};
	SDL_VERSION(&version);
	LogSDLVersion("We compiled against SDL version ", version);

	SDL_GetVersion(&version);
	LogSDLVersion("We linked against SDL version ", version);

	SDL_IMAGE_VERSION(&version);
	LogSDLVersion("We compiled against SDL_image version ", version);

	version = *IMG_Linked_Version();
	LogSDLVersion("We linked against SDL_image version ", version);

	SDL_TTF_VERSION(&version)
	LogSDLVersion("We compiled against SDL_ttf version ", version);

	version = *TTF_Linked_Version();
	LogSDLVersion("We linked against SDL_ttf version ", version);
}

mk::Minigin::Minigin(const std::filesystem::path &dataPath)
{
	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	g_window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (g_window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(g_window);
	ResourceManager::GetInstance().Init(dataPath);
}

mk::Minigin::~Minigin()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(g_window);
	g_window = nullptr;
	SDL_Quit();
}

void mk::Minigin::Run(const std::function<void()>& load)
{
	load();

	using namespace std::chrono;
	m_LastTime = high_resolution_clock::now();

#ifndef __EMSCRIPTEN__
	while (!m_quit)
		RunOneFrame();
#else
	emscripten_set_main_loop_arg(&LoopCallback, this, 0, true);
#endif
}

void mk::Minigin::RunOneFrame()
{
	using namespace std::chrono;
	constexpr std::chrono::milliseconds msPerFrame{ static_cast<long long>(1.f / FPS * 1000.f) };

	m_quit = !InputManager::GetInstance().ProcessInput();

	const auto currentTime{ high_resolution_clock::now() };
	const float deltaTime{ duration<float>(currentTime - m_LastTime).count()};
	m_LastTime = currentTime;
	m_Lag += deltaTime;

	// Update global time
	TimeManager& timeManager{ SceneManager::GetInstance().m_TimeManager };
	timeManager.deltaTime = deltaTime;

	while (m_Lag >= FIXED_TIME_STEP)
	{
		SceneManager::GetInstance().FixedUpdate();
		m_Lag -= FIXED_TIME_STEP;
	}

	SceneManager::GetInstance().Update();
	SceneManager::GetInstance().LateUpdate();
	Renderer::GetInstance().Render();

	//const auto sleepTime{ currentTime + milliseconds(msPerFrame) - high_resolution_clock::now() };
	//Sleep(static_cast<DWORD>(sleepTime.count() * timeTransform));
	const auto sleepTime{ currentTime + msPerFrame - high_resolution_clock::now() };

#undef max
	std::this_thread::sleep_for(sleepTime);
}
