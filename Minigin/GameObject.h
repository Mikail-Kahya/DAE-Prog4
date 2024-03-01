#pragma once
#include <list>
#include <string>
#include <memory>
#include <vector>

#include "Transform.h"
#include "Component.h"

namespace mk
{
	class Texture2D;

	class GameObject final
	{
	public:
		GameObject(const std::string& name = {});
		~GameObject();

		// TODO fix
		GameObject(const GameObject& other)				= delete;
		GameObject(GameObject&& other)					noexcept;
		GameObject& operator=(const GameObject& other)	= delete;
		GameObject& operator=(GameObject&& other)		noexcept;

		void Update();
		void FixedUpdate();
		void LateUpdate();

		void Destroy();
		void ClearDestroy();
		bool DestroyFlagged() const;

		const std::string& GetName() const;
		const glm::vec3& GetWorldPosition();

		void SetPosition(float x, float y);
		void SetPosition(float x, float y, float z);
		void SetPosition(const glm::vec3& position);
		void AddOffset(float x = 0.f, float y = 0.f, float z = 0.f);
		void AddOffset(const glm::vec3& offset);

		void SetParent(GameObject* parentPtr, bool keepWorldPosition = false);
		int GetChildCount() const;
		GameObject* GetChildAt(int index) const;

		template <std::derived_from<Component> ComponentType>
		[[nodiscard]] ComponentType* GetComponent() const;
		template <std::derived_from<Component> ComponentType, typename... Args>
		[[nodiscard]] ComponentType* AddComponent(const Args&... args);
		void RemoveComponent(const std::unique_ptr<Component>& component);


	private:
		void ComponentCleanup();
		void UpdateWorldPosition();
		void FlagPositionDirty();
		void AddChild(GameObject* childPtr);
		void RemoveChild(GameObject* childPtr);

		bool IsChild(GameObject* childPtr) const;

		// Common state
		std::string m_Name{};
		bool m_Destroy{};
		Transform m_LocalTransform{};
		Transform m_WorldTransform{};
		bool m_PositionIsDirty{ false };

		// Ownership
		GameObject* m_Parent{};
		std::vector<GameObject*> m_Children{};

		// Components
		std::list<std::unique_ptr<Component>> m_Components{};
		std::list<std::unique_ptr<Component>> m_ComponentBuffer{};
	};

	template <std::derived_from<Component> ComponentType>
	ComponentType* GameObject::GetComponent() const
	{
		auto componentIt = std::ranges::find_if(m_Components, [](const std::unique_ptr<Component>& component)
			{
				return dynamic_cast<ComponentType*>(component.get());
			});

		if (componentIt == m_Components.end())
			return nullptr;

		return dynamic_cast<ComponentType*>(componentIt->get());
	}

	template <std::derived_from<Component> ComponentType, typename... Args>
	ComponentType* GameObject::AddComponent(const Args&... args)
	{
		ComponentType* componentPtr{ GetComponent<ComponentType>() };
		if (componentPtr != nullptr)
			return componentPtr;

		std::unique_ptr<ComponentType> component{ std::make_unique<ComponentType>(args...) };
		component->SetOwner(this);
		component->Start();

		componentPtr = component.get();
		m_ComponentBuffer.emplace_back(std::move(component));
		return componentPtr;
	}
}
