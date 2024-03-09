#pragma once
#include <vector>

#include "GUIWidget.h"

namespace mk
{
	class GraphWidget : GUIWidget
	{
	public:
		GraphWidget(const std::vector<double>& data);
		~GraphWidget() override = default;

		GraphWidget(const GraphWidget& other)					= delete;
		GraphWidget(GraphWidget&& other) noexcept				= delete;
		GraphWidget& operator=(const GraphWidget& other)		= delete;
		GraphWidget& operator=(GraphWidget&& other)	noexcept	= delete;

		void Render() override;

	private:
		const std::vector<double> m_Times{};
	};
}
