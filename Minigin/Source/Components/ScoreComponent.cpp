#include "ScoreComponent.h"

using namespace mk;

void ScoreComponent::AddScore(const Event& event)
{
	int score{};
	event.GetData("score", score);

	m_Score += score;
		
	Print(std::to_string(m_Score) + "\n");
}
