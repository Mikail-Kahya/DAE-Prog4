#include "IObserver.h"
#include <algorithm>

using namespace mk;

IObserver::~IObserver()
{
	for (ISubject* subjectPtr : m_Subjects)
		subjectPtr->RemoveObserver(this);
}

void IObserver::OnNotify(ISubject* subjectPtr, const Event& event)
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

ISubject::~ISubject()
{
	for (IObserver* observerPtr : m_Observers)
		observerPtr->OnNotify(this, { EventType::OBJECT_DESTROY });
}

void ISubject::AddObserver(IObserver* observerPtr)
{
	const auto foundIter = std::find(m_Observers.begin(), m_Observers.end(), observerPtr);
	if (foundIter == m_Observers.end())
	{
		m_Observers.emplace_back(observerPtr);
		observerPtr->OnNotify(this, { EventType::OBSERVE });
	}
}

void ISubject::RemoveObserver(IObserver* observerPtr)
{
	const auto foundIter = std::find(m_Observers.begin(), m_Observers.end(), observerPtr);
	if (foundIter == m_Observers.end())
	{
		m_Observers.erase(foundIter);
		observerPtr->OnNotify(this, { EventType::STOP_OBSERVING });
	}
}

void ISubject::Notify(const Event& event)
{
	for (IObserver* observerPtr : m_Observers)
		observerPtr->OnNotify(this, event);
}
