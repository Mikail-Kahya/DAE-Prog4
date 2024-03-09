#include "GraphWidget.h"

#include "imgui.h"
#include "imgui_plot.h"

mk::GraphWidget::GraphWidget(const std::vector<double>& data)
	: m_Times{ data }
{
}

void mk::GraphWidget::Render()
{
    //ImGui::PlotConfig config{};
    //config.values.xs = x_data;
    //config.values.count = buf_size;
    //config.values.ys_list = y_data; // use ys_list to draw several lines simultaneously
    //config.values.ys_count = 3;
    //config.values.colors = colors;
    //config.scale.min = -1;
    //config.scale.max = 1;
    //config.tooltip.show = true;
    //config.grid_x.show = true;
    //config.grid_x.size = 128;
    //config.grid_x.subticks = 4;
    //config.grid_y.show = true;
    //config.grid_y.size = 0.5f;
    //config.grid_y.subticks = 5;
    //config.selection.show = true;
    //config.selection.length = &m_Times.size();
    //config.frame_size = ImVec2(buf_size, 200);
    //ImGui::Plot("plot1", conf);
    //
	//ImGui::PlotLines()
}
