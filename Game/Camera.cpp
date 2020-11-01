#include "Camera.h"

#include "WindowInfo.h"

namespace gnGame {

	Camera::Camera()
		: cameraPos({ WindowInfo::WindowWidth / 2.0f, WindowInfo::WindowHeight / 2.0f })
	{
	}

	void Camera::onStart()
	{

	}

	void Camera::onUpdate()
	{
		Debug::drawCircle(cameraPos, 10.f, Color::Red);
		Debug::drawFormatText(0, 0, Color::Black, "%s", cameraPos.toString().c_str());
	}

	void Camera::setTarget(Vector2& _target, const Vector2& _offset)
	{
		cameraPos = _target + _offset;
	}

	void Camera::scroll(Vector2& _vec)
	{
		cameraPos += {3.0f, 0.0f};

		if (cameraPos.x - WindowInfo::WindowWidth / 2.0f <= 0) {
			cameraPos.x = WindowInfo::WindowWidth / 2.0f;
		}
	}

	const Vector2 Camera::toScreenPos(const Vector2& _worldPos)
	{
		// カメラ座標からスクリーン座標の原点に変換
		auto screenOriginPos = Vector2{
			cameraPos.x - WindowInfo::WindowWidth / 2.0f,
			cameraPos.y - WindowInfo::WindowHeight / 2.0f
		};

		// ワールド座標からスクリーン座標に変換
		auto screenPos = Vector2{
			_worldPos.x - screenOriginPos.x,
			_worldPos.y - screenOriginPos.y
		};

		return screenPos;
	}

}