#include "MeasureWidget.h"

#include "imgui.h"

void mk::MeasureWidget::Render()
{
	ImGui::Begin("Exercise 2: Trash the cache");

	constexpr int bufferIncrease{ 1'000'000 };
	ImGui::InputInt("Buffer size", &m_BufferSize, bufferIncrease);
	m_BufferSize = std::max(0, m_BufferSize);
	ImGui::InputInt("Number of samples", &m_NrSamples, 1);
	m_NrSamples = std::max(0, m_NrSamples);

    if (ImGui::Button("Trash the cache with GameObject3D"))
        Measure<GameObject3D>("GameObject3D");

	if (ImGui::Button("Trash the cache with GameObject3DAlt"))
		Measure<GameObject3DAlt>("GameObject3DAlt");

	ImGui::End();
}