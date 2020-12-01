#include "../include/Camera.h"
#include "../include/WindowInfo.h"
#include "../include/Map.h"

namespace gnGame {

	Vector2 Camera::cameraPos{ WindowInfo::WindowWidth / 2.0f, WindowInfo::WindowHeight / 2.0f };

	Vector2 Camera::mapWide{};

	void Camera::setTarget(Vector2& _target, const Vector2& _offset)
	{
		cameraPos = _target + _offset;

		if (cameraPos.x - WindowInfo::WindowWidth / 2.0f <= 0.0f) {
			cameraPos.x = WindowInfo::WindowWidth / 2.0f;
		}

		if (cameraPos.x + WindowInfo::WindowWidth / 2.0f >= mapWide.x) {
			cameraPos.x = mapWide.x - WindowInfo::WindowWidth / 2.0f;
		}

		if (cameraPos.y - WindowInfo::WindowHeight / 2.0f <= 0.0f) {
			cameraPos.y = WindowInfo::WindowHeight / 2.0f;
		}

		if (cameraPos.y + WindowInfo::WindowHeight / 2.0f >= mapWide.y) {
			cameraPos.y = mapWide.y - WindowInfo::WindowHeight / 2.0f;
		}
	}

	void Camera::scroll(Vector2& _vec)
	{
		cameraPos += _vec;
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
		//return _worldPos;  // Test
	}

	void Camera::setMapInfo(const Vector2& _mapWide)
	{
		mapWide = _mapWide;
	}

	const Vector2 Camera::minScreenPos()
	{
		return {
			cameraPos.x - WindowInfo::WindowWidth / 2.0f,
			cameraPos.y - WindowInfo::WindowHeight / 2.0f
		};
	}

	const Vector2 Camera::maxScreenPos()
	{
		return {
			cameraPos.x + WindowInfo::WindowWidth / 2.0f,
			cameraPos.y + WindowInfo::WindowHeight / 2.0f
		};
	}
	bool Camera::isOnScreen(const Vector2& _pos)
	{
		auto minScrenn = Camera::minScreenPos();
		auto maxScreen = Camera::maxScreenPos();

		// 画面外でも描画するオフセット
		static float offset = 48.0f;

		return _pos.x + offset >= minScrenn.x && _pos.x - offset <= maxScreen.x
			&& _pos.y + offset >= minScrenn.y && _pos.y - offset <= maxScreen.y;
	}
}