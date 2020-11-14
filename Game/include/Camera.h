#ifndef CAMERA_H
#define CAMERA_H

#include "Lib.h"

#define CameraIns Camera::get()

namespace gnGame {

	/// <summary>
	/// プレイヤーを追跡するカメラ
	/// </summary>
	class Camera {
	private:
		static Camera* Instance;
		static Vector2 cameraPos;  // カメラ座標の原点の座標

	public:
		static Camera* get();
		static void destroy();

	public:
		Camera();
		~Camera();

		void setTarget(Vector2& _target, const Vector2& _offset = Vector2::Zero);
		void scroll(Vector2& _vec);

		// 座標をカメラに移るようにスクリーン座標に変換
		const Vector2 toScreenPos(const Vector2& _worldPos);
	};

}

#endif // !CAMERA_H
