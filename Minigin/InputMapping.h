#pragma once

#include <memory>
#include <map>

#include "Action.h"
#include "Command.h"

namespace mk
{
	class Command;

	class InputMapping final
	{
	public:
		//using Mapping = std::pair<std::unique_ptr<Command>, Action>;
		using Mappings = std::map<std::unique_ptr<Action>, std::unique_ptr<Command>>;

		InputMapping() = default;
		~InputMapping() = default;

		InputMapping(const InputMapping& other)					= delete;
		InputMapping(InputMapping&& other) noexcept				= default;
		InputMapping& operator=(const InputMapping& other)		= delete;
		InputMapping& operator=(InputMapping&& other) noexcept	= default;

		template<std::derived_from<Command> CommandType, typename... Args>
		void AddMapping(const Action& action, const Args&... args)
		{
			m_Mappings.emplace(std::make_unique<Action>(action), std::make_unique<CommandType>(args...));
		}

		const Mappings& GetMappings() const { return m_Mappings; }

	private:
		Mappings m_Mappings{};
	};
}
