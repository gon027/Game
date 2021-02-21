#include "../include/FrameTimer.h"
#include "../include/Lib.h"

namespace gnGame {

	FrameTimer::FrameTimer()
		: frameTime(0.0f)
		, timeScale(1.0f)
	{
	}

	void FrameTimer::update()
	{
		frameTime += Time::deltaTime() * timeScale;
	}

	void FrameTimer::reset()
	{
		frameTime = 0.0f;
	}

	void FrameTimer::setTime(float _time)
	{
		frameTime = _time;
	}

	void FrameTimer::setTimeScale(float _timeScale)
	{
		timeScale = _timeScale;
	}

	const bool FrameTimer::isTimeUp(float _time)
	{
		return frameTime >= _time;
	}

	const float FrameTimer::getFrameTime()
	{
		return frameTime;
	}

}