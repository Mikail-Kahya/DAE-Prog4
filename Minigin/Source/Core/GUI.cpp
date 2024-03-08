#include "GUI.h"

#include "imgui.h"
#include "SDL_video.h"
#include "SDL_render.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_sdlrenderer2.h"

void mk::GUI::Init(SDL_Window* windowPtr, SDL_Renderer* rendererPtr) const
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(windowPtr, SDL_GL_GetCurrentContext());
	ImGui_ImplSDLRenderer2_Init(rendererPtr);
}

void mk::GUI::BeginFrame() const
{
	ImGui_ImplSDLRenderer2_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();
}

void mk::GUI::EndFrame() const
{
	ImGui::Render();
	ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
}

void mk::GUI::Destroy()
{
	ImGui_ImplSDLRenderer2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}
