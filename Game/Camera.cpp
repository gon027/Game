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

	}

	void Camera::setTarget(Vector2& _target, const Vector2& _offset)
	{
		cameraPos = _target + _offset;

		if (cameraPos.x - WindowInfo::WindowWidth / 2.0f <= 0) {
			cameraPos.x = WindowInfo::WindowWidth / 2.0f;
		}
	}

	void Camera::scroll(Vector2& _vec)
	{
		cameraPos += _vec;
	}

	const Vector2 Camera::toScreenPos(const Vector2& _worldPos)
	{
		// �J�������W����X�N���[�����W�̌��_�ɕϊ�
		auto screenOriginPos = Vector2{
			cameraPos.x - WindowInfo::WindowWidth / 2.0f,
			cameraPos.y - WindowInfo::WindowHeight / 2.0f
		};

		// ���[���h���W����X�N���[�����W�ɕϊ�
		auto screenPos = Vector2{
			_worldPos.x - screenOriginPos.x,
			_worldPos.y - screenOriginPos.y
		};

		return screenPos;
		//return _worldPos;
	}

}