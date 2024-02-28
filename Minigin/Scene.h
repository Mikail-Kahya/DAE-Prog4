#pragma once
#include "SceneManager.h"
#include "GameObject.h"

namespace mk
{
	class Scene final
	{
	public:
		~Scene();
		Scene(const Scene& other)				= delete;
		Scene(Scene&& other)					= delete;
		Scene& operator=(const Scene& other)	= delete;
		Scene& operator=(Scene&& other)			= delete;

		void Start();
		
		void FixedUpdate();
		void Update();
		void LateUpdate();

		GameObject* SpawnObject(const std::string& name = { "None" });
		void RemoveAll();

	private: 
		explicit Scene(const std::string& name);
		friend Scene& SceneManager::CreateScene(const std::string& name);

		void CleanupGameObjects();

		std::string m_Name;
		std::vector <std::unique_ptr<GameObject>> m_Objects{};
		std::vector <std::unique_ptr<GameObject>> m_ObjectBuffer{};

		static unsigned int m_IdCounter; 
	};

}
