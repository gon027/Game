#ifndef CAMERA_H
#define CAMERA_H

#include "Lib.h"

#define CameraIns Camera::get()

namespace gnGame {

	/// <summary>
	/// �v���C���[��ǐՂ���J����
	/// </summary>
	class Camera {
	private:
		static Camera* Instance;
		static Vector2 cameraPos;  // �J�������W�̌��_�̍��W

	public:
		static Camera* get();
		static void destroy();

	public:
		Camera();
		~Camera();

		void setTarget(Vector2& _target, const Vector2& _offset = Vector2::Zero);
		void scroll(Vector2& _vec);

		// ���W���J�����Ɉڂ�悤�ɃX�N���[�����W�ɕϊ�
		const Vector2 toScreenPos(const Vector2& _worldPos);
	};

}

#endif // !CAMERA_H
