#pragma once
#include <string>

class Component
{
public:
	virtual ~Component(){}

	virtual void Update(){}
	virtual void Render() const{}

	void Destroy();
	void ClearDestroy();

	bool DestroyFlagged() const;

	Component(const Component& other)				= delete;
	Component(Component&& other)					= delete;
	Component& operator=(const Component& other)	= delete;
	Component& operator=(Component&& other)			= delete;

protected:
	Component(const std::string& name);

	std::string m_Name{};

private:
	bool m_Destroy{};
};