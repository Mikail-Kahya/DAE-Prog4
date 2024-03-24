#pragma once
#include "Observer.h"
#include "DebugUtils.h"

namespace mk
{
	class Test : public Component, public Observer
	{
	public:
		Test() = default;
		~Test() override = default;

		Test(const Test& other)					= delete;
		Test(Test&& other) noexcept				= delete;
		Test& operator=(const Test& other)		= delete;
		Test& operator=(Test&& other) noexcept	= delete;

		void OnNotify(Subject* subjectPtr, const Event& event) override
		{
			subjectPtr = nullptr;
			if (event.type == EventType::OBJECT_OVERLAP)
				Print("Hey " + std::to_string(idx) +  "\n");
			++idx;
		}

	private:
		int idx{};

	};
}
