#include "GUI.h"

#include "imgui.h"
#include "SDL_video.h"
#include "SDL_render.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_sdlrenderer2.h"

void mk::GUI::Init(SDL_Window* windowPtr, SDL_Renderer* rendererPtr)
{
	// Setup ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	m_Io = &ImGui::GetIO();

	// Setup rendering
	ImGui_ImplSDL2_InitForOpenGL(windowPtr, SDL_GL_GetCurrentContext());
	ImGui_ImplSDLRenderer2_Init(rendererPtr);

	// Set style
	ImGui::StyleColorsDark();
}

void mk::GUI::Render()
{
	BeginFrame();
	for (const auto& widget : m_Widgets)
		widget->Render();
	EndFrame();
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

void mk::GUI::Remove(GUIWidget* widgetPtr)
{
	const auto foundWidget = std::ranges::find_if(m_Widgets, [widgetPtr](const std::unique_ptr<GUIWidget>& widget)
	{
		return widget.get() == widgetPtr;
	});

	m_Widgets.erase(foundWidget);
}
