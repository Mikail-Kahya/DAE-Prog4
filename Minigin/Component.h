#pragma once
#include <memory>

namespace mk
{
	class GameObject;

	class Component
	{
	public:
		virtual ~Component() = default;

		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

		virtual void Start() {}

		virtual void Update() {}
		virtual void FixedUpdate() {}
		virtual void LateUpdate() {}

		void Destroy();
		void ClearDestroy();

		bool DestroyFlagged() const;

	protected:
		Component() = default;
		GameObject& GetOwner() const;

		friend class GameObject;

	private:
		void SetOwner(GameObject* ownerPtr);

		GameObject* m_OwnerPtr{};
		bool m_Destroy{};
	};
}


