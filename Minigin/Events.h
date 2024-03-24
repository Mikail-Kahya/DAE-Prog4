#pragma once
#include <cstdint>
#include <memory>

#include "DebugUtils.h"

namespace mk
{
	enum EventType
	{
		OBJECT_DESTROY,
		LEVEL_STARTED,
		LEVEL_ENDED,
		BOMB_EXPLODED,
		ENEMY_DIED,
		PLAYER_DIED
	};

	struct IEventArg
	{
		IEventArg() = default;
		virtual ~IEventArg() = default;
	};

	template<typename T>
	struct EventArg
	{
		explicit EventArg(T data) : m_Data{ data } {}

		T GetData() const { return m_Data; }
		void SetData(T data) { m_Data = data; }
	private:
		T m_Data;
	};

	struct Event
	{
		inline static const uint8_t MAX_ARGS{ 8 };

		EventType type{};
		uint8_t nrArgs{};

		template<typename T> bool SetData(uint8_t idx, T data)
		{
			if (IsOutRange(idx))
				return false;

			m_Args[idx] = std::make_unique<EventArg<T>>(data);
			return true;
		}

		template<typename T> bool GetData(uint8_t idx, T& data)
		{
			if (IsOutRange(idx))
				return false;

			EventArg<T>* p = dynamic_cast<EventArg<T>*>(m_Args[idx]);
			if (p != nullptr)
			{
				data = p->GetData();
				return true;
			}

			Print("Warning: Data not found on index " + std::to_string(idx) + "\n");
			return false;
		}

	private:
		bool IsOutRange(uint8_t idx) const
		{
			if (idx >= MAX_ARGS)
			{
				Print("Warning: Out of range\n");
				return false;
			}
			return true;
		}

		std::unique_ptr<IEventArg> m_Args[MAX_ARGS]{};
	};
}
