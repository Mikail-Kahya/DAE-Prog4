#include <stdexcept>
#include <cstring>
#include "Renderer.h"

#include <algorithm>

#include "GameObject.h"
#include "RenderComponent.h"
#include "SceneManager.h"
#include "Texture2D.h"

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
	m_window = window;
	m_renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}
}

void Renderer::Update()
{
	if (!m_DepthChanged)
		return;

	m_Renderers.sort([](RenderComponent* a, RenderComponent* b)
		{
			return a->GetOwner().GetWorldPosition().z > b->GetOwner().GetWorldPosition().z;
		});

	m_DepthChanged = false;
}

void Renderer::Render() const
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_renderer);

	for (RenderComponent* renderComponentPtr : m_Renderers)
	{
		if (renderComponentPtr->GetTexture() == nullptr)
			continue;

		const glm::vec3 position{ renderComponentPtr->GetOwner().GetWorldPosition() };
		RenderTexture(*renderComponentPtr->GetTexture(), position.x, position.y);
	}

	SDL_RenderPresent(m_renderer);
}

void Renderer::Destroy()
{
	if (m_renderer != nullptr)
	{
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
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
	m_AutoDepth -= depthSlice;
	return depth;
}

SDL_Renderer* Renderer::GetSDLRenderer() const { return m_renderer; }

void Renderer::RegisterRenderComponent(RenderComponent* renderComponentPtr)
{
	const auto foundIt = std::ranges::find(m_Renderers, renderComponentPtr);
	if (foundIt != m_Renderers.end())
		return;
	m_Renderers.push_front(renderComponentPtr);
	FlagDepthDirty();
}

void Renderer::UnregisterRenderComponent(RenderComponent* renderComponentPtr)
{
	std::erase(m_Renderers, renderComponentPtr);
}

void Renderer::FlagDepthDirty()
{
	m_DepthChanged = true;
}
