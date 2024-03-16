#pragma once

namespace mk
{
	class InputMapping
	{
	public:
		InputMapping() = default;
		~InputMapping() = default;

		InputMapping(const InputMapping& other)					= delete;
		InputMapping(InputMapping&& other) noexcept				= delete;
		InputMapping& operator=(const InputMapping& other)		= delete;
		InputMapping& operator=(InputMapping&& other) noexcept	= delete;

	private:
		
	};
}