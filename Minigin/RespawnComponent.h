#pragma once
#include "Component.h"
#include "Observer.h"
#include "glm/vec3.hpp"

namespace mk
{
	class RespawnComponent : public Component, public Observer
	{
	public:
		RespawnComponent(const glm::vec3& respawn);
		~RespawnComponent() override = default;

		RespawnComponent(const RespawnComponent& other)					= delete;
		RespawnComponent(RespawnComponent&& other) noexcept				= delete;
		RespawnComponent& operator=(const RespawnComponent& other)		= delete;
		RespawnComponent& operator=(RespawnComponent&& other) noexcept	= delete;

		void OnNotify(Subject* subjectPtr, const Event& event) override;
		void SetRespawn(const glm::vec3& respawn);

	private:
		void Respawn() const;

		glm::vec3 m_Respawn{};
	};
}
