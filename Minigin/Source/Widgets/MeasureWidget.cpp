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
    {
		//GUI::GetInstance().Remove(m_GameObjectPlot);
		std::vector<float> measures{};
		Measure<GameObject3DAlt>(measures);
		if (m_GameObjectPlot == nullptr)
			m_GameObjectPlot = GUI::GetInstance().Add<PlotWidget>("GameObject3D");
    	m_GameObjectPlot->AddGraph(std::move(measures));
    }
        

	if (ImGui::Button("Trash the cache with GameObject3DAlt"))
	{
		//GUI::GetInstance().Remove(m_GameObjectPlot);
		std::vector<float> measures{};
		Measure<GameObject3DAlt>(measures);
		if (m_AltObjectPlot == nullptr)
			m_AltObjectPlot = GUI::GetInstance().Add<PlotWidget>("GameObject3DAlt");
		m_AltObjectPlot->AddGraph(std::move(measures));
	}
		

	ImGui::End();
}