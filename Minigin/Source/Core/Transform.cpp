#include "Transform.h"

#include "Renderer.h"

mk::Transform::Transform()
{
	m_Position.z = Renderer::GetInstance().GetNextDepth();
}

void mk::Transform::AddOffset(const glm::vec3& offset)
{
	m_Position += offset;
}

void mk::Transform::AddOffset(float x, float y, float z)
{
	AddOffset({ x, y, z });
}

void mk::Transform::AddRotation(float x, float y, float z)
{
	m_Rotation.x += x;
	m_Rotation.y += y;
	m_Rotation.z += z;
}

void mk::Transform::AddScale(float x, float y, float z)
{
	m_Scale.x += x;
	m_Scale.y += y;
	m_Scale.z += z;
}

void mk::Transform::SetPosition(const glm::vec3& position)
{
	m_Position = position;
}

void mk::Transform::SetPosition(float x, float y, float z)
{
	SetPosition(glm::vec3{ x, y, z });
}

void mk::Transform::SetRotation(const glm::vec3& rotation)
{
	m_Rotation = rotation;
}

void mk::Transform::SetRotation(float x, float y, float z)
{
	SetRotation(glm::vec3{ x, y, z });
}

void mk::Transform::SetScale(const glm::vec3& scale)
{
	m_Scale = scale;
}

void mk::Transform::SetScale(float x, float y, float z)
{
	SetScale(glm::vec3{ x, y, z });
}
