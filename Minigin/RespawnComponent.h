#pragma once

namespace mk
{
	class X
	{
	public:
		X() = default;
		~X() = default;

		X(const X& other)					= delete;
		X(X&& other) noexcept				= delete;
		X& operator=(const X& other)		= delete;
		X& operator=(X&& other)	noexcept	= delete;

	private:
	};
}