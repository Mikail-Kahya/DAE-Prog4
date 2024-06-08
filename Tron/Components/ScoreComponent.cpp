#include "ScoreComponent.h"

#include "GameObject.h"
#include "TextComponent.h"
#include "Events/Events.h"

using namespace mk;


void ScoreComponent::Start()
{
	IComponent::Start();

	m_TextComponentPtr = GetOwner()->AddComponent<TextComponent>("Score: 0", "Lingua.otf", 30);
}

void ScoreComponent::OnNotify(ISubject* subjectPtr, IEvent* event)
{
	IObserver::OnNotify(subjectPtr, event);

	if (ObjectDiedEvent* diedEvent = dynamic_cast<ObjectDiedEvent*>(event))
		AddScore(diedEvent);
}

void ScoreComponent::AddScore(const ObjectDiedEvent* event)
{
	m_Score += event->score;
	m_TextComponentPtr->SetText("Score: " + std::to_string(m_Score));

	Notify(std::make_unique<ScoreChangedEvent>(m_Score));
}
