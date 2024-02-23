#pragma once
#include <string>
#include <memory>
#include <vector>

#include "Transform.h"
#include "Components/Component.h"
#include "Texture2D.h"

namespace dae
{
	class Texture2D;

	class GameObject final
	{
	public:
		GameObject(const std::string& name = {});
		~GameObject();

		// TODO fix
		GameObject(const GameObject& other);
		GameObject(GameObject&& other)					noexcept;
		GameObject& operator=(const GameObject& other);
		GameObject& operator=(GameObject&& other)		noexcept;

		void Update();
		void FixedUpdate();
		void LateUpdate();

		void Destroy();
		void ClearDestroy();
		bool DestroyFlagged() const;

		void SetPosition(float x, float y);

		template <std::derived_from<Component> ComponentType>
		Component* GetComponent();
		template <std::derived_from<Component> ComponentType>
		ComponentType* AddComponent();
		void RemoveComponent(const std::unique_ptr<Component>& component);

		std::string m_Name{};

	private:
		void ComponentCleanup();

		Transform m_Transform{};
		std::vector<std::unique_ptr<Component>> m_Components{};
		std::vector<std::unique_ptr<Component>> m_ComponentBuffer{};
		bool m_Destroy{};
	};

	template <std::derived_from<Component> ComponentType>
	Component* GameObject::GetComponent()
	{
		auto componentIt = std::ranges::find_if(m_Components, [](const std::unique_ptr<Component>& component)
			{
				return dynamic_cast<ComponentType>(component.get());
			});

		return (componentIt != m_Components.end()) ? *componentIt : nullptr;
	}

	template <std::derived_from<Component> ComponentType>
	ComponentType* GameObject::AddComponent()
	{
		std::unique_ptr<ComponentType> component{ std::make_unique<ComponentType>() };
		ComponentType* componentPtr{ component.get() };
		m_ComponentBuffer.emplace_back(std::move(component));
		return componentPtr;
	}
}
