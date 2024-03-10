#include "MeasureWidget.h"

#include "imgui.h"

void mk::MeasureWidget::Render()
{
	ImGui::Begin("Exercise 2: Trash the cache", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

	constexpr int bufferIncrease{ 1'000'000 };
	ImGui::InputInt("Buffer size", &m_BufferSize, bufferIncrease);
	m_BufferSize = std::max(0, m_BufferSize);
	ImGui::InputInt("Number of samples", &m_NrSamples, 1);
	m_NrSamples = std::max(0, m_NrSamples);

	constexpr float plotWidth{ 200.f };
	constexpr float plotHeight{ 100.f };
	bool reploted{};
    if (ImGui::Button("Trash the cache with GameObject3D"))
    {
		if (m_GameObjectPlot)
			m_GameObjectPlot->Destroy();

		std::vector<float> measures{};
		Measure<GameObject3D>(measures);
    	m_GameObjectPlot = GUI::GetInstance().Add<PlotWidget>("GameObject3D", plotWidth, plotHeight);
    	m_GameObjectPlot->AddGraph(measures);
		reploted = true;
    }

	if (m_GameObjectPlot != nullptr)
		m_GameObjectPlot->Plot();
        

	if (ImGui::Button("Trash the cache with GameObject3DAlt"))
	{
		if (m_AltObjectPlot)
			m_AltObjectPlot->Destroy();

		std::vector<float> measures{};
		Measure<GameObject3DAlt>(measures);
		m_AltObjectPlot = GUI::GetInstance().Add<PlotWidget>("GameObject3DAlt", plotWidth, plotHeight);
		m_AltObjectPlot->AddGraph(measures);
		reploted = true;
	}

	if (m_AltObjectPlot != nullptr)
		m_AltObjectPlot->Plot();

	if (m_GameObjectPlot != nullptr && m_AltObjectPlot != nullptr && reploted)
	{
		if (m_CombinedObjectPlot)
			m_CombinedObjectPlot->Destroy();

		m_CombinedObjectPlot = GUI::GetInstance().Add<PlotWidget>("Combined", plotWidth, plotHeight);
		m_CombinedObjectPlot->AddGraph(m_AltObjectPlot->GetData(0));
		m_CombinedObjectPlot->AddGraph(m_GameObjectPlot->GetData(0));
	}

	if (m_CombinedObjectPlot != nullptr)
		m_CombinedObjectPlot->Plot();

	ImGui::End();
}