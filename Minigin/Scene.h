#pragma once
#include "SceneManager.h"
#include "GameObject.h"

namespace dae
{
	class GameObject;
	class Scene final
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		~Scene();

		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		GameObject& CreateGameObject(const std::string& name);
		void RemoveAll();
		
		void Update();
		void FixedUpdate();
		void LateUpdate();
		void ObjectCleanup();
		void Render() const;

	private: 
		explicit Scene(const std::string& name);
		void RemoveDestroyed();

		std::string m_name;
		std::vector <GameObject> m_objects{};

		static unsigned int m_idCounter; 
	};
}
