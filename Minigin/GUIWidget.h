#pragma once

namespace mk
{
	class GUIWidget
	{
	public:
		virtual ~GUIWidget() = default;

		GUIWidget(const GUIWidget& other)					= delete;
		GUIWidget(GUIWidget&& other) noexcept				= delete;
		GUIWidget& operator=(const GUIWidget& other)		= delete;
		GUIWidget& operator=(GUIWidget&& other) noexcept	= delete;

		virtual void Render() = 0;
		void Destroy() { m_Destroy = true; }
		void ClearDestroy() { m_Destroy = false; }
		bool DestroyFlagged() const { return m_Destroy; }

	protected:
		GUIWidget() = default;

	private:
		bool m_Destroy{};
	};
}