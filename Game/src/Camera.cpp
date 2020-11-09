#include "../include/Camera.h"
#include "../include/WindowInfo.h"
#include "../include/Map.h"

namespace gnGame {

	Camera* Camera::Instance{ new Camera() };
	Vector2 Camera::cameraPos{ WindowInfo::WindowWidth / 2.0f, WindowInfo::WindowHeight / 2.0f };

	Camera::Camera()
	{

	}

	Camera::~Camera()
	{
		
	}

	Camera* Camera::get()
	{
		return Instance;
	}

	void Camera::destroy()
	{
		delete Instance;
		Instance = nullptr;
	}

	void Camera::onStart()
	{

	}

	void Camera::onUpdate()
	{

	}

	void Camera::setTarget(Vector2& _target, const Vector2& _offset)
	{
		cameraPos = _target + _offset;

		if (cameraPos.x - WindowInfo::WindowWidth / 2.0f <= 0.0f) {
			cameraPos.x = WindowInfo::WindowWidth / 2.0f;
		}

		if (cameraPos.x + WindowInfo::WindowWidth / 2.0f >= WorldMapSize::WorldMapWidth) {
			cameraPos.x = WorldMapSize::WorldMapWidth - WindowInfo::WindowWidth / 2.0f;
		}

		if (cameraPos.y - WindowInfo::WindowHeight / 2.0f <= 0.0f) {
			cameraPos.y = WindowInfo::WindowHeight / 2.0f;
		}

		if (cameraPos.y + WindowInfo::WindowHeight / 2.0f >= WorldMapSize::WorldMapHeight) {
			cameraPos.y = WorldMapSize::WorldMapHeight - WindowInfo::WindowHeight / 2.0f;
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
		//return _worldPos;
	}

}