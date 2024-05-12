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
		OBJECT_BLOCK,
		OBJECT_DIED,
		TAKE_DAMAGE,
		LEVEL_STARTED,
		LEVEL_ENDED,
		BOMB_EXPLODED,
		ENEMY_DIED,
		PLAYER_DIED,
		SCORE_CHANGED
	};

	struct IEventArg
	{
		IEventArg() = default;
		virtual ~IEventArg() = default;
	};

	template<typename T>
	struct EventArg : public IEventArg
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

		Event(const Event& other)					= delete;
		Event(Event&& other) noexcept;
		Event& operator=(const Event& other)		= delete;
		Event& operator=(Event&& other) noexcept;


		EventType type{};

		template<typename T> bool SetData(const std::string& key, T data)
		{
			if (!m_Args.contains(key))
			{
				m_Args[key] = std::make_unique<EventArg<T>>(data);
				return true;
			}

			EventArg<T>* dataPtr = dynamic_cast<EventArg<T>*>(m_Args.at(key).get());
			if (dataPtr == nullptr)
			{
				Print("Warning: Data already found on " + key + " but a different type\n");
				return false;
			}

			dataPtr->SetData(data);
			return true;
		}

		template<typename T> bool GetData(const std::string& key, T& data) const
		{
			if (!m_Args.contains(key))
				return false;
			EventArg<T>* dataPtr = dynamic_cast<EventArg<T>*>(m_Args.at(key).get());
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
