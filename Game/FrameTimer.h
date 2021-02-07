#ifndef FRAMETIMER_H
#define FRAMETIMER_H

namespace gnGame {

	class FrameTimer {
	public:
		FrameTimer();
		~FrameTimer() = default;

		// ���Ԃ��J�E���g�A�b�v������
		void update();

		// ���Z�b�g(���Ԃ�0�ɖ߂�)
		void reset();

		// �w�肵�����Ԃ𒴂�����
		bool isTimeUp(float _time);

	private:
		float frameTime;
	};
}

#endif // !FRAMETIMER_H