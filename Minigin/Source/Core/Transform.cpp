#include "Transform.h"

#include "Renderer.h"

mk::Transform::Transform()
{
	m_Position.z = Renderer::GetInstance().GetNextDepth();
}

void mk::Transform::AddWorldOffset(float x, float y, float z)
{
	m_Position.x += x;
	m_Position.y += y;
	m_Position.z += z;
}

void mk::Transform::SetPosition(float x, float y, float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}