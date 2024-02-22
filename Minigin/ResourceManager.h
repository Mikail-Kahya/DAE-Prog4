#pragma once
#include <filesystem>
#include <string>
#include <memory>
#include <map>

#include "Texture2D.h"
#include "Font.h"
#include "Singleton.h"

namespace dae
{

	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		~ResourceManager() override = default;

		ResourceManager(const ResourceManager& other)				= delete;
		ResourceManager(ResourceManager&& other)					= delete;
		ResourceManager& operator=(const ResourceManager& other)	= delete;
		ResourceManager& operator=(ResourceManager&& other)			= delete;

		void Init(const std::filesystem::path& data);

		Texture2D* LoadTexture(const std::string& file);
		Font* LoadFont(const std::string& file, unsigned int size);

	private:
		friend class Singleton<ResourceManager>;
		ResourceManager() = default;
		std::filesystem::path m_DataPath;

		std::map<std::string, std::unique_ptr<Texture2D>> m_Textures{};
		std::map<std::string, std::unique_ptr<Font>> m_Fonts{};
	};
}