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

		// FPS�̍X�V
		bool onUpdate();

		// ���߂������ԕ���~����
		void wait();

		// �f�o�b�O�p
		void drawFps();

	private:
		int startTime;
		int count;
		float fps;
	};
}

#endif // !FPS_H