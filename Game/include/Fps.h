#ifndef FPS_H
#define FPS_H

#include "Lib.h"

namespace gnGame {

	namespace Static {
		static constexpr int N = 60;
		static constexpr int FPS = 60;
	}

	class Fps {
	public:
		Fps()
			: startTime(0)
			, count(0)
			, fps(0)
		{}

		bool onUpdate() {
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

		void wait() {
			int tookTime = Time::getTime() - startTime;
			int waitTime = count * 1000 / Static::FPS - tookTime;
			if (waitTime > 0) {
				Sleep(waitTime);
			}
		}

		void draw() {
			//Debug::drawFormatText(35, 54, Color::Black, "Fps = %.1f", fps);
		}

	private:
		int startTime{ 0 };
		int count{ 0 };
		float fps{ 0.0f };

	};

}

#endif // !FPS_H