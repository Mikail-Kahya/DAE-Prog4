#pragma once
#include <list>
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
		friend class Singleton<Renderer>;
	public:
		void Init(int width, int height);
		void Update();
		void Render() const;
		void Destroy();

		float GetNextDepth();
		SDL_Renderer* GetSDLRenderer() const;
		int GetHeight() const noexcept;
		int GetWidth() const noexcept;

		const SDL_Color& GetBackgroundColor() const { return m_ClearColor; }
		void SetBackgroundColor(const SDL_Color& color) { m_ClearColor = color; }

		void RegisterRenderComponent(RenderComponent* renderComponentPtr);
		void UnregisterRenderComponent(RenderComponent* renderComponentPtr);
		void FlagDepthDirty();

	private:
		Renderer() = default;

		void RenderTexture(const Texture2D& texture, float x, float y) const;

		// Sorts by float. Whenever the float changes
		std::list<RenderComponent*> m_Renderers{};

		SDL_Renderer* m_Renderer{};
		SDL_Window* m_Window{};
		SDL_Color m_ClearColor{};

		float m_AutoDepth{};
		bool m_DepthChanged{ false };
		int m_Width{};
		int m_Height{};
	};
}

