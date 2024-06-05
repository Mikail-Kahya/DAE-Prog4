#pragma once
#include "IComponent.h"
#include "IObserver.h"
#include "glm/vec2.hpp"

namespace mk
{
	class RespawnComponent : public IComponent, public IObserver
	{
	public:
		RespawnComponent(const glm::vec2& respawn);
		~RespawnComponent() override = default;

		RespawnComponent(const RespawnComponent& other)					= delete;
		RespawnComponent(RespawnComponent&& other) noexcept				= delete;
		RespawnComponent& operator=(const RespawnComponent& other)		= delete;
		RespawnComponent& operator=(RespawnComponent&& other) noexcept	= delete;

		void OnNotify(ISubject* subjectPtr, IEvent* event) override;
		void SetRespawn(const glm::vec2& respawn);

	private:
		void Respawn() const;

		glm::vec2 m_Respawn{};
	};
}
