#pragma once
#include <forward_list>
#include <SDL.h>

#include "Singleton.h"

namespace mk
{
	class RenderComponent;
	class Texture2D;

	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
	public:
		void Init(SDL_Window* window);
		void Update();
		void Render() const;
		void Destroy();

		float GetNextDepth();
		SDL_Renderer* GetSDLRenderer() const;

		const SDL_Color& GetBackgroundColor() const { return m_clearColor; }
		void SetBackgroundColor(const SDL_Color& color) { m_clearColor = color; }

		void RegisterRenderComponent(RenderComponent* renderComponentPtr);
		void UnregisterRenderComponent(RenderComponent* renderComponentPtr);
		void FlagDepthDirty();

	private:
		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;

		// Sorts by float. Whenever the float changes
		std::forward_list<RenderComponent*> m_Renderers{};

		SDL_Renderer* m_renderer{};
		SDL_Window* m_window{};
		SDL_Color m_clearColor{};
		float m_AutoDepth{};
		bool m_DepthChanged{ false };
	};
}

