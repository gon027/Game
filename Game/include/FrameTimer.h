#ifndef FRAMETIMER_H
#define FRAMETIMER_H

namespace gnGame {

	/// <summary>
	/// フレームの時間をカウントするクラス
	/// </summary>
	class FrameTimer {
	public:
		FrameTimer();
		~FrameTimer() = default;

		// 時間をカウントアップさせる
		void update();

		// リセット(時間を0に戻す)
		void reset();

		// タイマーをセット
		void setTime(float _time);

		// 時間の加速度を設定する
		void setTimeScale(float _timeScale);

		// 指定した時間を超えたか
		const bool isTimeUp(float _time);

		// 現在の時間を取得する
		const float getFrameTime();

	private:
		float frameTime;
		float timeScale;
	};
}

#endif // !FRAMETIMER_H