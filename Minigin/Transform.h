#pragma once
#include <glm/glm.hpp>

namespace mk
{
	class Transform final
	{
	public:
		Transform();

		const glm::vec3& GetPosition() const { return m_Position; }

		void AddWorldOffset(float x = 0.f, float y = 0.f, float z = 0.f);

		void SetPosition(float x, float y, float z);


	private:
		glm::vec3 m_Position{};
		glm::vec3 m_Rotation{};
		glm::vec3 m_Scale{};
	};
}
