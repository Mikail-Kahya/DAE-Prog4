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

		PlotWidget(const std::string& graphName, float width = 100.f, float height = 100.f);
		~PlotWidget() override = default;

		PlotWidget(const PlotWidget& other)						= delete;
		PlotWidget(PlotWidget&& other) noexcept					= delete;
		PlotWidget& operator=(const PlotWidget& other)			= delete;
		PlotWidget& operator=(PlotWidget&& other)	noexcept	= delete;

		void Render() override{}
		void Plot() const;

		void AddGraph(const Graph& newGraph, ImColor color = {});
		void SetXAxis(std::vector<float>&& axis);
		const Graph& GetData(int graphIdx);

	private:
		ImColor GetRandomColor() const;

		std::vector<Graph> m_Graphs{};
		const std::string m_Name{};
		ImGui::PlotConfig m_Config{};
		std::vector<ImU32> m_Colors{};
		std::vector<const float*> m_DataList{};
		std::vector<float> m_XAxis{};
	};
}
