#ifndef FRAMETIMER_H
#define FRAMETIMER_H

namespace gnGame {

	class FrameTimer {
	public:
		FrameTimer();
		~FrameTimer() = default;

		// 時間をカウントアップさせる
		void update();

		// リセット(時間を0に戻す)
		void reset();

		// 指定した時間を超えたか
		bool isTimeUp(float _time);

	private:
		float frameTime;
	};
}

#endif // !FRAMETIMER_H