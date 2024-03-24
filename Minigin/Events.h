#pragma once
#include <memory>
#include <unordered_map>
#include "DebugUtils.h"

namespace mk
{
	enum EventType
	{
		OBSERVE,
		STOP_OBSERVING,
		OBJECT_DESTROY,
		OBJECT_OVERLAP,
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
		Event(EventType eventType) : type{ eventType }{}

		EventType type{};

		template<typename T> bool SetData(const std::string& key, T data)
		{
			if (!m_Args.contains(key))
				m_Args.emplace(key, std::make_unique<EventArg<T>>(data));


			EventArg<T>* dataPtr = dynamic_cast<EventArg<T>*>(m_Args[key]);
			if (dataPtr == nullptr)
			{
				Print("Warning: Data already found on " + key + " but a different type\n");
				return false;
			}

			dataPtr->SetData(data);
			return true;
		}

		template<typename T> bool GetData(const std::string& key, T& data)
		{
			EventArg<T>* dataPtr = dynamic_cast<EventArg<T>*>(m_Args[key]);
			if (dataPtr != nullptr)
			{
				data = dataPtr->GetData();
				return true;
			}

			Print("Warning: Data not found on " + key + "\n");
			return false;
		}

	private:
		std::unordered_map<std::string, std::unique_ptr<IEventArg>> m_Args{};
	};
}
