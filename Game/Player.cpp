#include "Player.h"
#include "WindowInfo.h"

namespace gnGame {

	constexpr float gravity = 0.98f;

	PlayerImage::PlayerImage()
		: texture("Image/char.png")
		, sprite(texture)
	{
	}

	Player::Player()
		: pImage()
		, pos()
		, velocity()
	{
	}

	void Player::onStart()
	{
		bounds.minPos.setPos(0, 0);
		bounds.maxPos.setPos(32, 64);
		bounds.size.setPos(bounds.maxPos - bounds.minPos);
		bounds.center.setPos(bounds.size.half());
	}

	void Player::onUpdate()
	{
		// �ړ��ϐ���
		float gy = gravity;

		// �ړ���
		if (Input::getKey(Key::A)) {
			pos.x -= 2.0f;
		}

		if (Input::getKey(Key::D)) {
			pos.x += 2.0f;
		}

		// ����{�b�N�X�X�V��
		bounds.minPos.setPos(pos.x - bounds.center.x, pos.y - bounds.center.y);
		bounds.maxPos.setPos(32 + pos.x - bounds.center.x, 64 + pos.y - bounds.center.y);
		bounds.size.setPos(bounds.maxPos - bounds.minPos);
		bounds.center.setPos(bounds.size.half());

		// �ړ����蕔
		if (pos.y + bounds.center.y >= WindowInfo::WindowHeight) {
			gy = 0;
		}

		pos.y += gy;

		// ���W�X�V��
		pImage.sprite.setPos(pos);


		// �`�敔
		pImage.sprite.draw();

		Debug::drawLine(bounds.minPos, Vector2{ bounds.minPos.x, bounds.maxPos.y }, 3.f, Color::Red);
		Debug::drawLine(bounds.minPos, Vector2{ bounds.maxPos.x, bounds.minPos.y }, 3.f, Color::Red);
		Debug::drawLine(Vector2{ bounds.maxPos.x, bounds.minPos.y }, bounds.maxPos, 3.f, Color::Red);
		Debug::drawLine(Vector2{ bounds.minPos.x, bounds.maxPos.y }, bounds.maxPos, 3.f, Color::Red);
	}

}