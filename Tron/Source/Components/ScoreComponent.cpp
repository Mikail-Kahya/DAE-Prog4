#include "ScoreComponent.h"

#include "GameObject.h"
#include "TextComponent.h"

using namespace mk;


void ScoreComponent::Start()
{
	Component::Start();

	m_TextComponentPtr = GetOwner()->AddComponent<TextComponent>("Score: 0", "Lingua.otf", 30);
}

void ScoreComponent::OnNotify(Subject* subjectPtr, const Event& event)
{
	Observer::OnNotify(subjectPtr, event);

	if (event.type == EventType::OBJECT_DIED)
		AddScore(event);
}

void ScoreComponent::AddScore(const Event& event)
{
	int scoreIncrease{};
	event.GetData("score", scoreIncrease);

	m_Score += scoreIncrease;
	m_TextComponentPtr->SetText("Score: " + std::to_string(m_Score));

	Event newEvent{ EventType::SCORE_CHANGED };
	newEvent.SetData("score", m_Score);
	Notify(newEvent);
}
