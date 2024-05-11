#pragma once

namespace mk
{
	class IState
	{
	public:
		virtual ~IState() = default;

		IState(const IState& other)					= delete;
		IState(IState&& other) noexcept				= delete;
		IState& operator=(const IState& other)		= delete;
		IState& operator=(IState&& other) noexcept	= delete;

		virtual void FixedUpdate() {}
		virtual void Update() {}
		virtual void LateUpdate() {}
		virtual std::unique_ptr<IState> TransitionState() = 0; // Force an override of transitioning
		virtual void OnEnter() {}
		virtual void OnExit() {}

	protected:
		IState() = default;
	};
}