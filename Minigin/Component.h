#pragma once
#include <memory>

namespace mk
{
	class GameObject;

	class Component
	{
	public:
		virtual ~Component() {}

		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

		virtual void Update() {}
		virtual void FixedUpdate() {}
		virtual void LateUpdate() {}

		void Destroy();
		void ClearDestroy();

		bool DestroyFlagged() const;

	protected:
		Component(GameObject* ownerPtr);
		GameObject& GetOwner() const;

	private:
		GameObject* m_OwnerPtr{};
		bool m_Destroy{};
	};
}


