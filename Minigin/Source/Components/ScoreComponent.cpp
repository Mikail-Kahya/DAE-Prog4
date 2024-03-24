#include "ScoreComponent.h"

#include "GameObject.h"
#include "TextComponent.h"

using namespace mk;


void ScoreComponent::Start()
{
	Component::Start();

	m_TextComponentPtr = GetOwner().AddComponent<TextComponent>("Score: 0");
}

void ScoreComponent::OnNotify(Subject* subjectPtr, const Event& event)
{
	Observer::OnNotify(subjectPtr, event);

	if (event.type == EventType::OBJECT_DIED)
		AddScore(event);
}

void ScoreComponent::AddScore(const Event& event)
{
	int score{};
	event.GetData("score", score);

	m_Score += score;
	m_TextComponentPtr->SetText("Score: " + std::to_string(m_Score));
}
