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
		constexpr float JumpPower = -7.0f;


		// �v���C���[�̐i�ދ���
		float getAxis() {
			float result = 0;
			if (Input::getKey(Key::A) || Input::getKey(Key::LEFT)) {
				result -= 1.0f;
			}

			if (Input::getKey(Key::D) || Input::getKey(Key::RIGHT)) {
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

	PlayerMoveInfo::PlayerMoveInfo()
		: isJump(false)
		, isSecondJump(false)
		, isGround(false)
	{
	}

	Player::Player(Map& _map)
		: map(_map)
		, pImage()
		, pos()
		, velocity()
		, isJump(false)
		, isGround(false)
		, pt()
		, pHit()
	{
	}

	void Player::onStart()
	{
		// -- ���W������ --
		pos.setPos(100, 350);

		bounds.minPos.setPos(0, 0);
		bounds.maxPos.setPos(32, 64);
		bounds.size.setPos(bounds.maxPos - bounds.minPos);
		bounds.center.setPos(bounds.size.half());
	}

	int frame = 0;

	void Player::onUpdate()
	{
		// ----- �ړ� -----
		velocity.x = PlayerInfo::getAxis() * PlayerInfo::Speed;
		
		// �W�����v�L�[�������ꂽ��
		if (Input::getKeyDown(Key::SPACE)) {
			// �n�ʂɑ������Ă���Ƃ�
			if (isGround) {
				isJump   = true;
				isGround = false;
			}
		}

		if (isJump) {
			++frame;
			velocity.y = PlayerInfo::JumpPower;

			if (frame == 30) {
				isJump = false;
				frame = 0;
			}
		}
		else {
			velocity.y = PlayerInfo::Gravity;
		}

		// ----- �ړ����� -----

		// velocity�����Z�����Ƃ��̍��W
		auto nextPos = pos + velocity;

		// ������s��
		if (nextPos.y + bounds.center.y >= 416) {
			velocity.y = 0;
			isGround = true;
		}

		//if (nextPos.x + bounds.center.x >= WindowInfo::WindowWidth) {
			//velocity.x = 0;
		//}

		if (nextPos.x - bounds.center.x <= 0) {
			velocity.x = 0;
		}

		// �E
		pHit.right[0] = Vector2{ bounds.maxPos.x, bounds.minPos.y };
		pHit.right[1] = Vector2{ bounds.maxPos.x, bounds.minPos.y + 16 };
		pHit.right[2] = Vector2{ bounds.maxPos.x, bounds.minPos.y + 32 };
		pHit.right[3] = Vector2{ bounds.maxPos.x, bounds.minPos.y + 48 };
		pHit.right[4] = Vector2{ bounds.maxPos.x, bounds.minPos.y + 64 };


		for (int i{}; i < 5; ++i) {
			if (map.getTile((int)pHit.right[i].x / 32, (int)pHit.right[i].y / 32) == MAP_TILE(2)
				|| pHit.right[1].x >= WindowInfo::WindowWidth || pHit.right[1].x <= 0.0f) {
				// ���������Ƃ���velocity�����Z�x�N�g�������߂�
				auto nextRightPos = pHit.right[i] + velocity;

				// ���������ꏊ�����߂�
				auto r = Vector2{ pHit.right[i].x / 32 * 32, pHit.right[i].y / 32 * 32 };

				// �����߂�
				pos.x = pos.x - fabsf(nextRightPos.x - r.x);

				break;
			}
		}

		// ----- ���W�X�V -----
		pos += velocity;

		// ����{�b�N�X�X�V
		bounds.minPos.setPos(pos.x - bounds.center.x, pos.y - bounds.center.y);
		bounds.maxPos.setPos(32 + pos.x - bounds.center.x, 64 + pos.y - bounds.center.y);

		pImage.sprite.setPos(pos);

		// ----- �`�� -----
		pImage.sprite.draw();

		// ----- �f�o�b�O -----
		debug();
	}

	void Player::debug()
	{
		Debug::drawFormatText(0, 0,   Color::Black, "Position = %s", pos.toString().c_str());
		Debug::drawFormatText(0, 20,  Color::Black, "Velocity = %s", velocity.toString().c_str());
		Debug::drawFormatText(0, 40,  Color::Black, "isGround = %d", isGround);
		Debug::drawFormatText(0, 60,  Color::Black, "isJump   = %d", isJump);
		Debug::drawFormatText(0, 80,  Color::Black, "frame    = %d", frame);
		Debug::drawFormatText(0, 100, Color::Black, "Block    = %d", map.getTile((int)bounds.maxPos.x / 32, (int)bounds.maxPos.y / 32));
		Debug::drawFormatText(0, 120, Color::Black, "BlockPos = %d, %d", (int)bounds.maxPos.x / 32, (int)bounds.maxPos.y / 32);

		/*
		Debug::drawLine(bounds.minPos, Vector2{ bounds.minPos.x, bounds.maxPos.y }, 1.f, Color::Red);
		Debug::drawLine(bounds.minPos, Vector2{ bounds.maxPos.x, bounds.minPos.y }, 1.f, Color::Red);
		Debug::drawLine(Vector2{ bounds.maxPos.x, bounds.minPos.y }, bounds.maxPos, 1.f, Color::Red);
		Debug::drawLine(Vector2{ bounds.minPos.x, bounds.maxPos.y }, bounds.maxPos, 1.f, Color::Red);
		*/

		for (auto& v : pHit.right) {
			pt.setColor(Color::Green);
			pt.setPos(v);
			pt.draw();
		}
	}
}