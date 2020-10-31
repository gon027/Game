#ifndef CAMERA_H
#define CAMERA_H

#include "Lib.h"

namespace gnGame {

	/// <summary>
	/// プレイヤーを追跡するカメラ
	/// </summary>
	class Camera {
	public:
		Camera();
		~Camera() = default;

		void onStart();
		void onUpdate();

		// 座標をカメラに移るようにスクリーン座標に変換
		const Vector2 toScreenPos(const Vector2& _worldPos);

	private:
		Vector2 cameraPos;  // カメラ座標の原点の座標
	};

}

#endif // !CAMERA_H
