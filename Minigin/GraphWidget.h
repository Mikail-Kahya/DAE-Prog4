#pragma once
#include "GUIWidget.h"

namespace mk
{
	class GraphWidget : GUIWidget
	{
	public:
		GraphWidget() = default;
		~GraphWidget() override = default;

		GraphWidget(const GraphWidget& other)					= delete;
		GraphWidget(GraphWidget&& other) noexcept				= delete;
		GraphWidget& operator=(const GraphWidget& other)		= delete;
		GraphWidget& operator=(GraphWidget&& other)	noexcept	= delete;

	private:
	};
}
