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
		cameraPos += Vector2{ 0.1f, 0.0f };
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
	}

}