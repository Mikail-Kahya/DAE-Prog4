#pragma once
#include <string>
#include <chrono>
#include <numeric>
#include <valarray>
#include <vector>

#include "GUIWidget.h"
#include "GUI.h"
#include "PlotWidget.h"

namespace mk
{
	class MeasureWidget : public GUIWidget
	{
	public:
		MeasureWidget(const std::string& name);
		~MeasureWidget() override = default;
		
		MeasureWidget(const MeasureWidget& other)					= delete;
		MeasureWidget(MeasureWidget&& other) noexcept				= delete;
		MeasureWidget& operator=(const MeasureWidget& other)		= delete;
		MeasureWidget& operator=(MeasureWidget&& other)	noexcept	= delete;

		void Render() override;

	private:
		struct Transform
		{
			float matrix[16]
			{
				1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1
			};
		};

		class GameObject3D
		{
		public:
			Transform local;
			int id;

			GameObject3D& operator*=(int scalar)
			{
				id *= scalar;
				return *this;
			}
		};

		class GameObject3DAlt
		{
		public:
			Transform* local;
			int id;

			GameObject3DAlt& operator*=(int scalar)
			{
				id *= scalar;
				return *this;
			}
		};

		template <typename ObjType>
		void Measure(std::vector<float>& measures);

		void Exercise1();
		void Exercise2();

		void RenderInput(); // both use the same inputs

		template <typename MeasureValueType>
		void HandlePlot(PlotWidget*& plotPtr, const std::string& plotName);

		static constexpr float PLOT_WIDTH{ 200.f };
		static constexpr float PLOT_HEIGHT{ 100.f };

		int m_BufferSize{ 10'000'000 };
		int m_NrSamples{ 50 };
		PlotWidget* m_IntPlot{};
		PlotWidget* m_GameObjectPlot{};
		PlotWidget* m_AltObjectPlot{};
		PlotWidget* m_CombinedObjectPlot{};
	};

	template <typename ObjType>
	void MeasureWidget::Measure(std::vector<float>& measures)
	{
		using namespace std::chrono;

		std::vector<ObjType> buffer(m_BufferSize);

		for (int stepSize{ 1 }; stepSize <= 1024; stepSize *= 2)
		{
			std::vector<int> samples{};

			for (int measureIdx{}; measureIdx < m_NrSamples; ++measureIdx)
			{
				const auto start{ high_resolution_clock::now() };

				for (int idx{}; idx < m_BufferSize; idx += stepSize)
					buffer[idx] *= 2;

				const auto end{ high_resolution_clock::now() };
				samples.push_back(static_cast<int>(duration_cast<microseconds> (end - start).count()));
			}

			std::ranges::sort(samples);
			measures.push_back(std::accumulate(std::next(samples.begin()), std::prev(samples.end()), 0.f) / (m_NrSamples - 2));
		}
	}

	template <typename MeasureValueType>
	void MeasureWidget::HandlePlot(PlotWidget*& plotPtr, const std::string& plotName)
	{
		if (plotPtr)
			plotPtr->Destroy();

		std::vector<float> measures{};
		Measure<MeasureValueType>(measures);
		plotPtr = GUI::GetInstance().Add<PlotWidget>(plotName, PLOT_WIDTH, PLOT_HEIGHT);
		plotPtr->AddGraph(measures);

		// add x axis
		const size_t nrElements{ measures.size() };
		measures.clear();
		measures.resize(nrElements);
		std::iota(measures.begin(), measures.end(), 0.f);
		for (float& measure : measures)
			measure = std::pow(2.f, measure);
		plotPtr->SetXAxis(std::move(measures));
	}
}
