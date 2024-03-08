#pragma once
#include <glm/glm.hpp>

namespace mk
{
	class Transform final
	{
	public:
		Transform();

		const glm::vec3& GetPosition() const { return m_Position; }
		const glm::vec3& GetRotation() const { return m_Rotation; }
		const glm::vec3& GetScale() const { return m_Scale; }

		void AddOffset(const glm::vec3& offset);
		void AddOffset(float x = 0.f, float y = 0.f, float z = 0.f);
		void AddRotation(float x = 0.f, float y = 0.f, float z = 0.f);
		void AddScale(float x = 0.f, float y = 0.f, float z = 0.f);

		void SetPosition(const glm::vec3& position);
		void SetPosition(float x, float y, float z);
		void SetRotation(const glm::vec3& rotation);
		void SetRotation(float x, float y, float z);
		void SetScale(const glm::vec3& scale);
		void SetScale(float x, float y, float z);

	private:
		glm::vec3 m_Position{};
		glm::vec3 m_Rotation{};
		glm::vec3 m_Scale{};
	};
}
