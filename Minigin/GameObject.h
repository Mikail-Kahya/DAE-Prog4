#pragma once
#include <string>
#include <memory>
#include <vector>

#include "Transform.h"
#include "Component.h"

namespace dae
{
	class Texture2D;
	class GameObject
	{
		Transform m_transform{};
		std::shared_ptr<Texture2D> m_texture{};
	public:
		virtual void FixedUpdate();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render() const;

		void Destroy();
		void ClearDestroy();
		bool DestroyFlagged() const;


		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);


		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	protected:
		template <typename  ComponentType, typename... Args>
		void AddComponent(const std::string& name, Args... arguments);
		void RemoveComponent(std::unique_ptr<Component> component);


	private:
		void RemoveComponents();

		std::vector<std::unique_ptr<Component>> m_Components{};
		bool m_Destroy{};
	};

	template <typename ComponentType, typename... Args>
	void GameObject::AddComponent(const std::string& name, Args... arguments)
	{
		m_Components.emplace_back(std::make_unique<ComponentType>(name, arguments));
	}
}
