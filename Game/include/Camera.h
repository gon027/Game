#ifndef CAMERA_H
#define CAMERA_H

#include "Lib.h"

namespace gnGame {

	/// <summary>
	/// �J�����N���X
	/// </summary>
	class Camera {
	private:
		static Vector2 cameraPos;  // �J�������W�̌��_�̍��W

	public:
		// �ǐՂ�����W���Z�b�g
		static void setTarget(Vector2& _target, const Vector2& _offset = Vector2::Zero);

		// Todo : �X�N���[������Ƃ��Ɏ�������
		static void scroll(Vector2& _vec);

		// ���W���J�����Ɉڂ�悤�ɃX�N���[�����W�ɕϊ�
		static const Vector2 toScreenPos(const Vector2& _worldPos);

		// �J�������ڂ��Ă���ŏ��̍��W���擾
		static const Vector2 minScreenPos();

		// �J�������ڂ��Ă���ő�̍��W���擾
		static const Vector2 maxScreenPos();
	};
}

#endif // !CAMERA_H
