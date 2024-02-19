#pragma once

class Component
{
public:
	virtual ~Component(){}

	virtual void Update(){}
	virtual void Render() const{}

	Component(const Component& other)				= delete;
	Component(Component&& other)					= delete;
	Component& operator=(const Component& other)	= delete;
	Component& operator=(Component&& other)			= delete;

protected:
	Component(){}
};