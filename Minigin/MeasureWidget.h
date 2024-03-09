#pragma once
#include <string>
#include <chrono>
#include <numeric>
#include <vector>
#include <iostream>

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
		};

		class GameObject3DAlt
		{
		public:
			Transform* local;
			int id;
		};

		template <typename ObjType>
		void Measure(const std::string& plotName) const;

		int m_BufferSize{ 10'000'000 };
		int m_NrSamples{ 50 };
	};

	template <typename ObjType>
	void MeasureWidget::Measure(const std::string& plotName) const
	{
		using namespace std::chrono;

		std::vector<ObjType> buffer(m_BufferSize);

		std::vector<double> endTimes{};

		for (int stepSize{ 1 }; stepSize <= 1024; stepSize *= 2)
		{
			std::vector<int> samples{};

			for (int measureIdx{}; measureIdx < m_NrSamples; ++measureIdx)
			{
				const auto start{ high_resolution_clock::now() };

				for (int idx{}; idx < m_BufferSize; idx += stepSize)
					buffer[idx].id *= 2;

				const auto end{ high_resolution_clock::now() };
				samples.push_back(static_cast<int>(duration_cast<microseconds> (end - start).count()));
			}

			std::ranges::sort(samples);
			endTimes.push_back(std::accumulate(std::next(samples.begin()), std::prev(samples.end()), 0.0) / (m_NrSamples - 2));
		}

		std::cout << plotName;
	}
}
