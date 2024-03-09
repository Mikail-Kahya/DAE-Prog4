#include "MeasureWidget.h"

#include "imgui.h"
#include "DebugUtils.h"

void mk::MeasureWidget::Render()
{
	ImGui::Begin("Exercise 2: Trash the cache");

	if (ImGui::Button("Button"))
		Print("Works\n");

	ImGui::End();
}
