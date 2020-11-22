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
		Fps();
		~Fps() = default;

		// FPSの更新
		bool onUpdate();

		// 超過した時間分停止する
		void wait();

		// デバッグ用
		void drawFps();

	private:
		int startTime;
		int count;
		float fps;
	};
}

#endif // !FPS_H