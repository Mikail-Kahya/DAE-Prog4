#pragma once
#include <memory>

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

	virtual std::unique_ptr<Component> Clone() = 0;

protected:
	Component() = default;

private:
	bool m_Destroy{};
};
