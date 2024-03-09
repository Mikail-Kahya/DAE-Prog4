#pragma once
#include "GUIWidget.h"

namespace mk
{
	class MeasureWidget : public GUIWidget
	{
	public:
		MeasureWidget() = default;
		~MeasureWidget() override = default;

		MeasureWidget(const MeasureWidget& other)					= delete;
		MeasureWidget(MeasureWidget&& other) noexcept				= delete;
		MeasureWidget& operator=(const MeasureWidget& other)		= delete;
		MeasureWidget& operator=(MeasureWidget&& other)	noexcept	= delete;

		void Render() override;

	private:
	};
}