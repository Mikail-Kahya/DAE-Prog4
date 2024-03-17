#pragma once

#include <memory>
#include <unordered_map>

#include "Action.h"
#include "Command.h"

namespace mk
{
	class Command;

	class InputMapping final
	{
	public:
		using Mappings = std::unordered_map <std::unique_ptr<Command>, Action>;
		using Mapping = std::pair<std::unique_ptr<Command>, Action>;

		InputMapping() = default;
		~InputMapping() = default;

		InputMapping(const InputMapping& other) = default;
		InputMapping(InputMapping&& other) noexcept = default;
		InputMapping& operator=(const InputMapping& other) = default;
		InputMapping& operator=(InputMapping&& other) noexcept = default;

		template<std::derived_from<Command> CommandType, typename... Args>
		void AddInput(const Action& action, Command* commandPtr, const Args&...);

		const Mappings& GetMappings() const;

	private:
		Mappings m_Mappings;
	};

	template <std::derived_from<Command>  CommandType, typename ... Args>
	void InputMapping::AddInput(const Action& action, Command* commandPtr, const Args&... args)
	{
		m_Mappings.insert({ std::make_unique<CommandType>(args...), action });
	}
}