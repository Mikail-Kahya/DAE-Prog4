#pragma once

#include <memory>
#include <vector>

#include "Action.h"
#include "Command.h"

namespace mk
{
	class Command;

	class InputMapping final
	{
	public:
		using Mapping = std::pair<Action, std::unique_ptr<Command>>;
		using Mappings = std::vector<Mapping>;

		InputMapping() = default;
		~InputMapping() = default;

		InputMapping(const InputMapping& other)					= default;
		InputMapping(InputMapping&& other) noexcept				= default;
		InputMapping& operator=(const InputMapping& other)		= default;
		InputMapping& operator=(InputMapping&& other) noexcept	= default;

		template<std::derived_from<Command> CommandType, typename... Args>
		void AddMapping(const Action& action, const Args&... args)
		{
			m_Mappings.emplace_back(std::make_pair(action, std::make_unique<CommandType>(args...)));
		}

		const Mappings& GetMappings() const { return m_Mappings; }

	private:
		Mappings m_Mappings{};
	};
}
