#pragma once

namespace mk
{
	class PhysicsSystem
	{
	public:
		PhysicsSystem() = default;
		~PhysicsSystem() = default;

		PhysicsSystem(const PhysicsSystem& other)					= delete;
		PhysicsSystem(PhysicsSystem&& other) noexcept				= delete;
		PhysicsSystem& operator=(const PhysicsSystem& other)		= delete;
		PhysicsSystem& operator=(PhysicsSystem&& other)	noexcept	= delete;

	private:
	};
}