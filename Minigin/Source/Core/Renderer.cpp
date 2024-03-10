#include <stdexcept>
#include <cstring>
#include "imgui.h"

#include "Renderer.h"

#include "GameObject.h"
#include "RenderComponent.h"
#include "SceneManager.h"
#include "Texture2D.h"
#include "GUI.h"

using namespace mk;

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void Renderer::Init(SDL_Window* window)
{
	m_Window = window;
	m_Renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}
	GUI::GetInstance().Init(window, GetSDLRenderer());
}

void Renderer::Update()
{
	GUI::GetInstance().Update();

	if (!m_DepthChanged)
		return;

	m_Renderers.sort([](RenderComponent* a, RenderComponent* b)
		{
			return a->GetRenderDepth() < b->GetRenderDepth();
		});

	m_DepthChanged = false;
}

void Renderer::Render() const
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_Renderer);

	for (RenderComponent* renderComponentPtr : m_Renderers)
	{
		if (renderComponentPtr->GetTexture() == nullptr)
			continue;

		const glm::vec2 position{ renderComponentPtr->GetRenderPosition() };
		RenderTexture(*renderComponentPtr->GetTexture(), position.x, position.y);
	}

	GUI::GetInstance().Render();

	SDL_RenderPresent(m_Renderer);
}

void Renderer::Destroy()
{
	GUI::GetInstance().Destroy();
	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}
}

void Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

float Renderer::GetNextDepth()
{
	constexpr float depthSlice{ 0.1f };
	const float depth{ m_AutoDepth };
	m_AutoDepth += depthSlice;
	return depth;
}

SDL_Renderer* Renderer::GetSDLRenderer() const { return m_Renderer; }

void Renderer::RegisterRenderComponent(RenderComponent* renderComponentPtr)
{
	const auto foundIt = std::ranges::find(m_Renderers, renderComponentPtr);
	if (foundIt != m_Renderers.end())
		return;

	// Place in right order to avoid full resort
	const float newDepth{ renderComponentPtr->GetRenderDepth() };

	const auto lowerBoundIt = std::ranges::find_if(m_Renderers,
		[newDepth](const RenderComponent* a)
		{
			const float aDepth{ a->GetRenderDepth() };
			return aDepth < newDepth;
		});
	

	if (lowerBoundIt == m_Renderers.end())
		m_Renderers.push_front(renderComponentPtr);
	else if (lowerBoundIt == m_Renderers.begin())
		m_Renderers.push_back(renderComponentPtr);
	else
		m_Renderers.insert(std::prev(lowerBoundIt), renderComponentPtr);
}

void Renderer::UnregisterRenderComponent(RenderComponent* renderComponentPtr)
{
	std::erase(m_Renderers, renderComponentPtr);
}

void Renderer::FlagDepthDirty()
{
	m_DepthChanged = true;
}
