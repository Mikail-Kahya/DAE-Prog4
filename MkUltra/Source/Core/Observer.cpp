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
	switch (event.type)
	{
	case OBSERVE:
		subjectPtr->AddObserver(this);
		break;
	case STOP_OBSERVING:
	case OBJECT_DESTROY:
		subjectPtr->RemoveObserver(this);
		break;
	}
}

Subject::~Subject()
{
	for (Observer* observerPtr : m_Observers)
		observerPtr->OnNotify(this, { EventType::OBJECT_DESTROY });
}

void Subject::AddObserver(Observer* observerPtr)
{
	const auto foundIter = std::find(m_Observers.begin(), m_Observers.end(), observerPtr);
	if (foundIter == m_Observers.end())
	{
		m_Observers.emplace_back(observerPtr);
		observerPtr->OnNotify(this, { EventType::OBSERVE });
	}
}

void Subject::RemoveObserver(Observer* observerPtr)
{
	const auto foundIter = std::find(m_Observers.begin(), m_Observers.end(), observerPtr);
	if (foundIter == m_Observers.end())
	{
		m_Observers.erase(foundIter);
		observerPtr->OnNotify(this, { EventType::STOP_OBSERVING });
	}
}

void Subject::Notify(const Event& event)
{
	for (Observer* observerPtr : m_Observers)
		observerPtr->OnNotify(this, event);
}
