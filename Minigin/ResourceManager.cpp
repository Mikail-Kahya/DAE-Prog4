#include <stdexcept>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "ResourceManager.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "Font.h"

void dae::ResourceManager::Init(const std::filesystem::path& dataPath)
{
	m_DataPath = dataPath;

	if (TTF_Init() != 0)
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}

dae::Texture2D* dae::ResourceManager::LoadTexture(const std::string& file)
{
	// Check if texture was loaded before
	if (m_Textures.contains(file))
		return m_Textures.at(file).get();

	// Load new texture
	const auto fullPath = m_DataPath/file;
	auto texture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.string().c_str());
	if (texture == nullptr)
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());

	std::unique_ptr texture2D{ std::make_unique<Texture2D>(texture) };
	Texture2D* texturePtr{ texture2D.get() };
	m_Textures[file] = std::move(texture2D);

	return texturePtr;
}

std::shared_ptr<dae::Font> dae::ResourceManager::LoadFont(const std::string& file, unsigned int size) const
{
	const auto fullPath = m_DataPath/file;
	return std::make_shared<Font>(fullPath.string(), size);
}
