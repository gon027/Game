#ifndef CAMERA_H
#define CAMERA_H

#include "Lib.h"

namespace gnGame {

	/// <summary>
	/// カメラクラス
	/// </summary>
	class Camera {
	private:
		static Vector2 cameraPos;  // カメラ座標の原点の座標

	public:
		// 追跡する座標をセット
		static void setTarget(Vector2& _target, const Vector2& _offset = Vector2::Zero);

		// Todo : スクロールするときに実装する
		static void scroll(Vector2& _vec);

		// 座標をカメラに移るようにスクリーン座標に変換
		static const Vector2 toScreenPos(const Vector2& _worldPos);

		// カメラが移している最小の座標を取得
		static const Vector2 minScreenPos();

		// カメラが移している最大の座標を取得
		static const Vector2 maxScreenPos();
	};
}

#endif // !CAMERA_H
