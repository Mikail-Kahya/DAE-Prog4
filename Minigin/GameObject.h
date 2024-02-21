#pragma once
#include <string>
#include <memory>
#include <vector>

#include "Transform.h"
#include "Component.h"

namespace dae
{
	class Texture2D;
	class GameObject final
	{
	public:
		GameObject(const std::string& name = {});
		~GameObject();

		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Update();
		void FixedUpdate();
		void LateUpdate();
		void Render() const;
		void ComponentCleanup();

		void Destroy();
		void ClearDestroy();
		bool DestroyFlagged() const;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		template <typename ComponentType>
		requires std::derived_from<ComponentType, Component>
		Component* GetComponent();
		template <typename ComponentType, typename... Args>
		requires std::derived_from<ComponentType, Component>
		void AddComponent(const std::string& name, Args... arguments);
		void RemoveComponent(const std::unique_ptr<Component>& component);

		std::string m_Name{};

	private:
		Transform m_transform{};
		std::shared_ptr<Texture2D> m_texture{};

		std::vector<std::unique_ptr<Component>> m_Components{};
		bool m_Destroy{};
	};

	template <typename ComponentType>
	requires std::derived_from<ComponentType, Component>
	Component* GameObject::GetComponent()
	{
		auto componentIt = std::ranges::find_if(m_Components, [](const std::unique_ptr<Component>& component)
			{
				return dynamic_cast<ComponentType>(component.get());
			});

		return (componentIt != m_Components.end()) ? *componentIt : nullptr;
	}

	template <typename ComponentType, typename... Args>
	requires std::derived_from<ComponentType, Component>
	void GameObject::AddComponent(const std::string& name, Args... arguments)
	{
		m_Components.emplace_back(std::make_unique<ComponentType>(name, arguments));
	}
}