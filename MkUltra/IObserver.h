#pragma once
#include "Events.h"
#include <vector>

namespace mk 
{
	class ISubject;
	class GameObject;

	class IObserver
	{
	public:
		IObserver() = default;
		virtual ~IObserver();
		virtual void OnNotify(ISubject* subjectPtr, const Event& event);

	private:
		std::vector<ISubject*> m_Subjects{};
	};

	class ISubject
	{
	public:
		ISubject() = default;
		virtual ~ISubject();

		void AddObserver(IObserver* observerPtr);
		void RemoveObserver(IObserver* observerPtr);

	protected:
		void Notify(const Event& event);

	private:
		std::vector<IObserver*> m_Observers{};
	};
}