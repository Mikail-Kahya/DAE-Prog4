#pragma once
#include <list>
#include <string>
#include <memory>
#include <vector>

#include "Transform.h"

namespace mk
{

	class Component;
	class Texture2D;

	class GameObject final
	{
	public:
		GameObject(const std::string& name = {});
		~GameObject();

		// TODO fix
		GameObject(const GameObject& other)					= delete;
		GameObject(GameObject&& other) noexcept;
		GameObject& operator=(const GameObject& other)		= delete;
		GameObject& operator=(GameObject&& other) noexcept;

		void Update();
		void FixedUpdate();
		void LateUpdate();

		void Destroy();
		void ClearDestroy();
		bool DestroyFlagged() const;

		const std::string& GetName() const;
		const glm::vec3& GetWorldPosition();
		const glm::vec3& GetLocalPosition() const;
		float GetRotation();
		glm::vec3 GetForward();
		bool IsStatic() const;

		void SetLocalPosition(float x, float y);
		void SetLocalPosition(const glm::vec3& position);
		void AddLocalOffset(const glm::vec2& offset);
		void SetRotation(float rotation);
		void AddRotation(float deltaRotation);
		void SetStatic(bool isStatic);

		// TODO: Keep world rotation?
		void SetParent(GameObject* parentPtr, bool keepWorldPosition = false);
		GameObject* GetParent() const;
		int GetChildCount() const;
		GameObject* GetChildAt(int index) const;

		template <std::derived_from<Component> ComponentType>
		[[nodiscard]] ComponentType* GetComponent() const;
		template <std::derived_from<Component> ComponentType, typename... Args>
		ComponentType* AddComponent(const Args&... args);
		void RemoveComponent(const std::unique_ptr<Component>& component);


	private:
		void ComponentCleanup();
		void UpdateWorldPosition();
		void UpdateWorldRotation();
		void FlagPositionDirty();
		void FlagRotationDirty();
		void AddChild(GameObject* childPtr);
		void RemoveChild(GameObject* childPtr);

		bool IsChild(GameObject* childPtr) const;

		// Ownership
		GameObject* m_Parent{};
		std::vector<GameObject*> m_Children{};

		// Components
		std::vector<std::unique_ptr<Component>> m_Components;
		std::vector<std::unique_ptr<Component>> m_ComponentBuffer;

		// Common state
		std::string m_Name{};
		Transform m_LocalTransform;
		Transform m_WorldTransform;
		bool m_PositionIsDirty{ false };
		bool m_RotationIsDirty{ false };
		bool m_IsStatic{ false };
		bool m_Destroy{ false };
	};

	template <std::derived_from<Component> ComponentType>
	ComponentType* GameObject::GetComponent() const
	{
		auto componentIt = std::ranges::find_if(m_Components, [](const std::unique_ptr<Component>& component)
			{
				return dynamic_cast<ComponentType*>(component.get());
			});

		if (componentIt != m_Components.end())
			return dynamic_cast<ComponentType*>(componentIt->get());

		componentIt = std::ranges::find_if(m_ComponentBuffer, [](const std::unique_ptr<Component>& component)
			{
				return dynamic_cast<ComponentType*>(component.get());
			});

		if (componentIt != m_ComponentBuffer.end())
			return dynamic_cast<ComponentType*>(componentIt->get());

		return nullptr;
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
