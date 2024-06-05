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

	if (PlayerDiedEvent* diedEvent = dynamic_cast<PlayerDiedEvent*>(event))
		AddScore(diedEvent);
}

void ScoreComponent::AddScore(const PlayerDiedEvent* event)
{
	m_Score += event->score;
	m_TextComponentPtr->SetText("Score: " + std::to_string(m_Score));

	Notify(std::make_unique<ScoreChangedEvent>(m_Score));
}
