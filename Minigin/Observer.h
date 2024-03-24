#pragma once
#include "Events.h"

#include <vector>

namespace mk 
{
	class Subject;
	class GameObject;

	class Observer
	{
	public:
		Observer() = default;
		virtual ~Observer();
		virtual void OnNotify(Subject* subjectPtr, const Event& event);

		void Observe(Subject* subjectPtr);
		void StopObserving(Subject* subjectPtr);

	private:
		std::vector<Subject*> m_Subjects{};
	};

	class Subject
	{
	public:
		Subject() = default;
		virtual ~Subject();

		void AddObserver(Observer* observerPtr);
		void RemoveObserver(Observer* observerPtr);

	protected:
		void Notify(const Event& event);

	private:
		std::vector<Observer*> m_Observers{};
	};
}