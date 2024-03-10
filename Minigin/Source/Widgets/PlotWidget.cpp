#include "PlotWidget.h"

#include <numeric>

#include "imgui.h"

mk::PlotWidget::PlotWidget(const std::string& graphName, float width, float height)
	: m_Name{ graphName }
{
	m_Config.scale.min = 0;
	m_Config.frame_size = ImVec2(width, height);
	m_Config.line_thickness = 2.f;

	m_Config.v_lines.show = true;
	m_Config.skip_small_lines = false;

	m_Config.tooltip.show = true;
	m_Config.tooltip.format = "x=%.2f, y=%.2f";
	m_Config.grid_x.show = true;
	m_Config.grid_y.show = true;
}

void mk::PlotWidget::AddGraph(Graph&& newGraph)
{
	const float maxScale{ *std::ranges::max_element(newGraph) };
	const int nrValues{ std::max(m_Config.values.count, static_cast<int>(newGraph.size())) };

	m_Colors.push_back(GetRandomColor());
	m_DataList.push_back(newGraph.data());

	m_Graphs.push_back(std::move(newGraph));

	m_Config.scale.max = std::max(m_Config.scale.max, maxScale);
	m_Config.values.count = nrValues;
	m_Config.values.colors = m_Colors.data();
	m_Config.values.ys_list = m_DataList.data();
	m_Config.values.ys_count = static_cast<int>(m_Graphs.size());
}

void mk::PlotWidget::Plot()
{
	ImGui::Plot(m_Name.c_str(), m_Config);
}

ImColor mk::PlotWidget::GetRandomColor() const
{
	return{
		rand() % 255,
		rand() % 255,
		rand() % 255
	};
}
