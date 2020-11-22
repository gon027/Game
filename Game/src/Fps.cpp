#include "../include/Fps.h"

namespace gnGame {
	Fps::Fps()
		: startTime(0)
		, count(0)
		, fps(0)
	{
	}

	bool Fps::onUpdate()
	{
		if (count == 0) {
			startTime = Time::getTime();
		}

		if (count == Static::N) {
			int t = Time::getTime();
			fps = 1000.0f / ((t - startTime) / (float)Static::N);
			count = 0;
			startTime = t;
		}

		count++;
		return true;
	}

	void Fps::wait() 
	{
		int tookTime = Time::getTime() - startTime;
		int waitTime = count * 1000 / Static::FPS - tookTime;
		if (waitTime > 0) {
			Sleep(waitTime);
		}
	}

	void Fps::drawFps() 
	{
		Debug::drawFormatText(0, 20, Color::Black, "Fps = %.1f", fps);
	}

}