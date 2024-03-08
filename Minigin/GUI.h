#pragma once

// design inspired by Matias Devred

struct SDL_Window;
struct SDL_Renderer;

namespace mk
{
	class GUI final
	{
	public:
		GUI() = default;
		~GUI() = default;

		GUI(const GUI& other)				= delete;
		GUI(GUI&& other)					= delete;
		GUI& operator=(const GUI& other)	= delete;
		GUI& operator=(GUI&& other)			= delete;

		void Init(SDL_Window* windowPtr, SDL_Renderer* rendererPtr) const;
		void BeginFrame() const;
		void EndFrame() const;
		void Destroy();

	private:
	};
}