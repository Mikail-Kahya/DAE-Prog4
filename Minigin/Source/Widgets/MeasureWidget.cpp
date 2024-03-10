#include "MeasureWidget.h"

#include "imgui.h"

void mk::MeasureWidget::Render()
{
	Exercise1();
	Exercise2();
}

void mk::MeasureWidget::Exercise1()
{
	ImGui::Begin("Exercise 1: Trash the cache", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	RenderInput();

	if (ImGui::Button("Trash the cache with int"))
		HandlePlot<int>(m_IntPlot, "Int");

	if (m_IntPlot != nullptr)
		m_IntPlot->Plot();

	ImGui::End();
}

void mk::MeasureWidget::Exercise2()
{
	ImGui::Begin("Exercise 2: Trash the cache", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	RenderInput();

	bool reploted{};
	if (ImGui::Button("Trash the cache with GameObject3D"))
	{
		HandlePlot<GameObject3D>(m_GameObjectPlot, "GameObject3D");
		reploted = true;
	}

	if (m_GameObjectPlot != nullptr)
		m_GameObjectPlot->Plot();


	if (ImGui::Button("Trash the cache with GameObject3DAlt"))
	{
		HandlePlot<GameObject3DAlt>(m_AltObjectPlot, "GameObject3DAlt");
		reploted = true;
	}

	if (m_AltObjectPlot != nullptr)
		m_AltObjectPlot->Plot();

	if (m_GameObjectPlot != nullptr && m_AltObjectPlot != nullptr && reploted)
	{
		if (m_CombinedObjectPlot)
			m_CombinedObjectPlot->Destroy();

		m_CombinedObjectPlot = GUI::GetInstance().Add<PlotWidget>("Combined", PLOT_WIDTH, PLOT_HEIGHT);
		m_CombinedObjectPlot->AddGraph(m_AltObjectPlot->GetData(0));
		m_CombinedObjectPlot->AddGraph(m_GameObjectPlot->GetData(0));
	}

	if (m_CombinedObjectPlot != nullptr)
	{
		ImGui::Text("Combined:");
		m_CombinedObjectPlot->Plot();
	}

	ImGui::End();
}

void mk::MeasureWidget::RenderInput()
{
	constexpr int bufferIncrease{ 1'000'000 };
	ImGui::InputInt("Buffer size", &m_BufferSize, bufferIncrease);
	m_BufferSize = std::max(0, m_BufferSize);
	ImGui::InputInt("Number of samples", &m_NrSamples, 1);
	m_NrSamples = std::max(0, m_NrSamples);
}
