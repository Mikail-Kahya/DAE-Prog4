#pragma once
#include <SDL.h>
#include <unordered_set>

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
		void Render() const;
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;

		float GetNextDepth();
		SDL_Renderer* GetSDLRenderer() const;

		const SDL_Color& GetBackgroundColor() const { return m_clearColor; }
		void SetBackgroundColor(const SDL_Color& color) { m_clearColor = color; }

		void RegisterRenderComponent(RenderComponent* renderComponentPtr);
		void UnregisterRenderComponent(RenderComponent* renderComponentPtr);

	private:

		// Set to avoid accidental double rendering
		std::unordered_set<RenderComponent*> m_RenderComponentPtrs{};

		SDL_Renderer* m_renderer{};
		SDL_Window* m_window{};
		SDL_Color m_clearColor{};
		float m_AutoDepth{};
	};
}

