#pragma once
#include <string>
#include <vector>

#include "GUIWidget.h"
#include "imgui_plot.h"

namespace mk
{
	class PlotWidget : public GUIWidget
	{
	public:
		using Graph = std::vector<float>;

		PlotWidget(const std::string& graphName);
		~PlotWidget() override = default;

		PlotWidget(const PlotWidget& other)					= delete;
		PlotWidget(PlotWidget&& other) noexcept				= delete;
		PlotWidget& operator=(const PlotWidget& other)		= delete;
		PlotWidget& operator=(PlotWidget&& other)	noexcept	= delete;

		void Render() override;

		void AddGraph(Graph&& newGraph);

	private:
		ImColor GetRandomColor() const;

		std::vector<Graph> m_Graphs{};
		const std::string m_Name{};
		ImGui::PlotConfig m_Config{};
		std::vector<ImU32> m_Colors{};
		std::vector<const float*> m_DataList{};
	};
}
