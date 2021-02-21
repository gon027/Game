#ifndef FRAMETIMER_H
#define FRAMETIMER_H

namespace gnGame {

	/// <summary>
	/// �t���[���̎��Ԃ��J�E���g����N���X
	/// </summary>
	class FrameTimer {
	public:
		FrameTimer();
		~FrameTimer() = default;

		// ���Ԃ��J�E���g�A�b�v������
		void update();

		// ���Z�b�g(���Ԃ�0�ɖ߂�)
		void reset();

		// �^�C�}�[���Z�b�g
		void setTime(float _time);

		// ���Ԃ̉����x��ݒ肷��
		void setTimeScale(float _timeScale);

		// �w�肵�����Ԃ𒴂�����
		const bool isTimeUp(float _time);

		// ���݂̎��Ԃ��擾����
		const float getFrameTime();

	private:
		float frameTime;
		float timeScale;
	};
}

#endif // !FRAMETIMER_H