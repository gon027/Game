#include "Player.h"
#include "WindowInfo.h"
#include <cmath>

namespace gnGame {

	namespace PlayerInfo {
		// �v���C���[�ɂ�����d��
		constexpr float Gravity = 0.98f;

		// �v���C���[���i�ޑ���
		constexpr float Speed = 5.0f;

		// �v���C���[�̃W�����v��
		constexpr float JumpPower = 7.0f;


		// �v���C���[�̐i�ދ���
		float getAxis() {
			float result = 0;
			if (Input::getKey(Key::A)) {
				result -= 1.0f;
			}

			if (Input::getKey(Key::D)) {
				result += 1.0f;
			}

			return result;
		}
	};

	PlayerImage::PlayerImage()
		: texture("Image/char.png")
		, sprite(texture)
	{
	}

	Player::Player()
		: pImage()
		, pos(100, 100)
		, velocity()
		, isJump(false)
		, isGround(false)
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
		float gy = PlayerInfo::Gravity;

		// �ړ���
		pos.x += PlayerInfo::getAxis() * PlayerInfo::Speed;

		if (Input::getKeyDown(Key::SPACE)) {
			//isJump = 1;
			pos.x = 300.f;

			if (isGround) {
				isGround = false;
				isJump = 1;
				pos.y -= PlayerInfo::JumpPower;
				isJump = 0;
			}
		}


		// ����{�b�N�X�X�V��
		bounds.minPos.setPos(pos.x - bounds.center.x, pos.y - bounds.center.y);
		bounds.maxPos.setPos(32 + pos.x - bounds.center.x, 64 + pos.y - bounds.center.y);
		bounds.size.setPos(bounds.maxPos - bounds.minPos);
		bounds.center.setPos(bounds.size.half());

		// �ړ����蕔
		if (pos.y + bounds.center.y >= 416) {
			gy = 0;
			isGround = true;
		}


		if (pos.x + bounds.center.x >= WindowInfo::WindowWidth) {
			pos.x = WindowInfo::WindowWidth - bounds.center.x;
		}

		if (pos.x - bounds.center.x <= 0) {
			pos.x = 0 + bounds.center.x;
		}

		pos.y += gy;

		// ���W�X�V��
		pImage.sprite.setPos(pos);


		// �`�敔
		pImage.sprite.draw();

		debug();
	}

	void Player::debug()
	{
		Debug::drawFormatText(0, 0, Color::Black, "Pos = %s", pos.toString().c_str());
		Debug::drawFormatText(0, 20, Color::Black, "isGround = %d", isGround);
		Debug::drawFormatText(0, 40, Color::Black, "isJump   = %d", isJump);

		Debug::drawLine(bounds.minPos, Vector2{ bounds.minPos.x, bounds.maxPos.y }, 3.f, Color::Red);
		Debug::drawLine(bounds.minPos, Vector2{ bounds.maxPos.x, bounds.minPos.y }, 3.f, Color::Red);
		Debug::drawLine(Vector2{ bounds.maxPos.x, bounds.minPos.y }, bounds.maxPos, 3.f, Color::Red);
		Debug::drawLine(Vector2{ bounds.minPos.x, bounds.maxPos.y }, bounds.maxPos, 3.f, Color::Red);
	}
}