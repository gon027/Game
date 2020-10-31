#ifndef CAMERA_H
#define CAMERA_H

#include "Lib.h"

namespace gnGame {

	/// <summary>
	/// �v���C���[��ǐՂ���J����
	/// </summary>
	class Camera {
	public:
		Camera();
		~Camera() = default;

		void onStart();
		void onUpdate();

		// ���W���J�����Ɉڂ�悤�ɃX�N���[�����W�ɕϊ�
		const Vector2 toScreenPos(const Vector2& _worldPos);

	private:
		Vector2 cameraPos;  // �J�������W�̌��_�̍��W
	};

}

#endif // !CAMERA_H
