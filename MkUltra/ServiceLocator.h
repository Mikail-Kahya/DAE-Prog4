#pragma once

namespace mk
{
	class ServiceLocator final
	{
	public:
		~ServiceLocator() = default;

		ServiceLocator(const ServiceLocator& other)					= delete;
		ServiceLocator(ServiceLocator&& other) noexcept				= delete;
		ServiceLocator& operator=(const ServiceLocator& other)		= delete;
		ServiceLocator& operator=(ServiceLocator&& other) noexcept	= delete;

	private:
		ServiceLocator() = default;
	};
}