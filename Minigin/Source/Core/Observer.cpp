#include "Observer.h"
#include <algorithm>

using namespace mk;

Observer::~Observer()
{
	for (Subject* subjectPtr : m_Subjects)
		subjectPtr->RemoveObserver(this);
}

void Observer::OnNotify(Subject* subjectPtr, const Event& event)
{
	if (event.type == EventType::OBJECT_DESTROY)
		StopObserving(subjectPtr);
}

void Observer::Observe(Subject* subjectPtr)
{
	const auto foundIter = std::find(m_Subjects.begin(), m_Subjects.end(), subjectPtr);
	if (foundIter == m_Subjects.end())
		m_Subjects.emplace_back(subjectPtr);
}

void Observer::StopObserving(Subject* subjectPtr)
{
	const auto foundIter = std::find(m_Subjects.begin(), m_Subjects.end(), subjectPtr);
	m_Subjects.erase(foundIter);
}

Subject::~Subject()
{
	for (Observer* observerPtr : m_Observers)
		observerPtr->OnNotify(this, {});
}

void Subject::AddObserver(Observer* observerPtr)
{
	const auto foundIter = std::find(m_Observers.begin(), m_Observers.end(), observerPtr);
	if (foundIter == m_Observers.end())
		m_Observers.emplace_back(observerPtr);
}

void Subject::RemoveObserver(Observer* observerPtr)
{
	const auto foundIter = std::find(m_Observers.begin(), m_Observers.end(), observerPtr);
	m_Observers.erase(foundIter);
}

void Subject::Notify(const Event& event)
{
	for (Observer* observerPtr : m_Observers)
		observerPtr->OnNotify(this, event);
}
