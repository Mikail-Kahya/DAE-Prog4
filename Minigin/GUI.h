#pragma once
#include <concepts>
#include <memory>
#include <vector>

#include "Singleton.h"
#include "GUIWidget.h"
#include "SDL_events.h"

// design inspired by Matias Devred

struct ImGuiIO;
struct SDL_Window;
struct SDL_Renderer;

namespace mk
{
	class GUI final : public Singleton<GUI>
	{
	public:
		GUI() = default;
		~GUI() override = default;

		GUI(const GUI& other)					= delete;
		GUI(GUI&& other) noexcept				= delete;
		GUI& operator=(const GUI& other)		= delete;
		GUI& operator=(GUI&& other)	noexcept	= delete;

		void Init(SDL_Window* windowPtr, SDL_Renderer* rendererPtr);
		void AddSdlEvents(const SDL_Event& event);
		void Render();
		void Destroy();

		template<class WidgetType, typename... Args>
		requires(std::derived_from<WidgetType, GUIWidget>)
		[[nodiscard]] WidgetType* Add(const Args&... args);
		void Remove(GUIWidget* widgetPtr);

	private:
		void BeginFrame() const;
		void EndFrame() const;

		std::vector<std::unique_ptr<GUIWidget>> m_Widgets{};
		ImGuiIO* m_Io{};
	};

	template <class WidgetType, typename ... Args> requires (std::derived_from<WidgetType, GUIWidget>)
	WidgetType* GUI::Add(const Args&... args)
	{
		std::unique_ptr<WidgetType> widget{ std::make_unique<WidgetType>(args...) };
		WidgetType* widgetPtr{ widget.get() };

		m_Widgets.emplace_back(std::move(widget));
		return widgetPtr;
	}
}
