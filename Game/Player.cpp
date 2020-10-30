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
		: texture("Image/player.png")
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
		bounds.maxPos.setPos(32, 32);
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
			velocity.y = 5.f;

			// �n�ʂɑ������Ă���Ƃ�
			if (isGround) {
				isJump   = true;
			}
		}

		if (isJump) {
			isGround = false;
			++frame;
			velocity.y = PlayerInfo::JumpPower;

			if (frame == 15) {
				isJump = false;
				frame = 0;
			}
		}
		else {
			velocity.y = PlayerInfo::Gravity;
		}

		// ----- �ړ����� -----

		int size = 2;

		// -- �E(-) --
		pHit.right[0] = Vector2{ bounds.maxPos.x, bounds.minPos.y + 8 };
		pHit.right[1] = Vector2{ bounds.maxPos.x, bounds.minPos.y + 24 };

		for (int i{}; i < size; ++i) {
			if (map.getTile((int)pHit.right[i].x / 32, (int)pHit.right[i].y / 32) == MAP_TILE(2)
				|| pHit.right[i].x >= WindowInfo::WindowWidth) {

				// ���������Ƃ���velocity�����Z�x�N�g�������߂�
				float nextRightPos = pHit.right[i].x + velocity.x;

				// ���������ꏊ�����߂�
				float r = pHit.right[i].x / 32 * 32;

				// �����߂�
				// * Pos�𒼐ڂ�����̂ł͂Ȃ��Avelocity�ɑ��삳����ق�����������
				pos.x = pos.x - fabsf(nextRightPos - r);

				break;
			}
		}

		// -- ��(+) --
		pHit.left[0] = Vector2{ bounds.minPos.x, bounds.minPos.y + 8 };
		pHit.left[1] = Vector2{ bounds.minPos.x, bounds.minPos.y + 24 };

		for (int i{}; i < size; ++i) {
			if (map.getTile((int)pHit.left[i].x / 32, (int)pHit.left[i].y / 32) == MAP_TILE(2)
				|| pHit.left[i].x <= 0) {
				// ���������Ƃ���velocity�����Z�x�N�g�������߂�
				float nextRightPos = pHit.left[i].x + velocity.x;

				// ���������ꏊ�����߂�
				float r = pHit.left[i].x / 32 * 32;

				// �����߂�
				// * Pos�𒼐ڂ�����̂ł͂Ȃ��Avelocity�ɑ��삳����ق�����������
				pos.x = pos.x + fabsf(nextRightPos - r);

				break;
			}
		}

		// -- ��(+) --
		pHit.top[0] = Vector2{ bounds.minPos.x + 8,  bounds.minPos.y };
		pHit.top[1] = Vector2{ bounds.minPos.x + 24, bounds.minPos.y };

		for (int i{}; i < size; ++i) {
			if (map.getTile((int)pHit.top[i].x / 32, (int)pHit.top[i].y / 32) == MAP_TILE(2)
				|| pHit.top[i].y <= 0.0f) {

				// ���������Ƃ���velocity�����Z�x�N�g�������߂�
				auto nextRightPos = pHit.top[i].y + velocity.y;

				// ���������ꏊ�����߂�
				auto r = pHit.top[i].y / 32 * 32;

				// �����߂�
				pos.y = pos.y + fabsf(nextRightPos - r);

				break;
			}
		}

		// -- ��(-) --
		pHit.bottom[0] = Vector2{ bounds.minPos.x + 8,  bounds.maxPos.y };
		pHit.bottom[1] = Vector2{ bounds.minPos.x + 24, bounds.maxPos.y };

		for (int i{}; i < size; ++i) {
			if (map.getTile((int)pHit.bottom[i].x / 32, (int)pHit.bottom[i].y / 32) == MAP_TILE(2)
				|| pHit.bottom[i].y >= WindowInfo::WindowHeight) {

				// ���������Ƃ���velocity�����Z�x�N�g�������߂�
				auto nextRightPos = pHit.bottom[i].y + velocity.y;

				// ���������ꏊ�����߂�
				auto r = pHit.bottom[i].y / 32 * 32;

				// �����߂�
				pos.y = pos.y - fabsf(nextRightPos - r);

				isGround = true;

				break;
			}
		}

		// ----- ���W�X�V -----
		pos += velocity;

		// ����{�b�N�X�X�V
		bounds.minPos.setPos(pos.x - bounds.center.x, pos.y - bounds.center.y);
		bounds.maxPos.setPos(32 + pos.x - bounds.center.x, 32 + pos.y - bounds.center.y);

		pImage.sprite.setPos(pos);

		// ----- �`�� -----
		pImage.sprite.draw();

		// ----- �f�o�b�O -----
		debug();
	}

	void Player::debug()
	{
#ifndef DEBUG
		Debug::drawFormatText(0, 0,   Color::Black, "Position = %s", pos.toString().c_str());
		Debug::drawFormatText(0, 20,  Color::Black, "Velocity = %s", velocity.toString().c_str());
		Debug::drawFormatText(0, 40,  Color::Black, "isGround = %d", isGround);
		Debug::drawFormatText(0, 60,  Color::Black, "isJump   = %d", isJump);
		Debug::drawFormatText(0, 80,  Color::Black, "frame    = %d", frame);
		Debug::drawFormatText(0, 100, Color::Black, "Block    = %d", map.getTile((int)bounds.maxPos.x / 32, (int)bounds.maxPos.y / 32));
		Debug::drawFormatText(0, 120, Color::Black, "BlockPos = %d, %d", (int)bounds.maxPos.x / 32, (int)bounds.maxPos.y / 32);

		Debug::drawLine(bounds.minPos, Vector2{ bounds.minPos.x, bounds.maxPos.y }, 1.f, Color::Green);
		Debug::drawLine(bounds.minPos, Vector2{ bounds.maxPos.x, bounds.minPos.y }, 1.f, Color::Green);
		Debug::drawLine(Vector2{ bounds.maxPos.x, bounds.minPos.y }, bounds.maxPos, 1.f, Color::Green);
		Debug::drawLine(Vector2{ bounds.minPos.x, bounds.maxPos.y }, bounds.maxPos, 1.f, Color::Green);

		for (auto& v : pHit.right) {
			pt.setColor(Color::Red);
			pt.setPos(v);
			pt.draw();
		}

		for (auto& v : pHit.left) {
			pt.setColor(Color::Red);
			pt.setPos(v);
			pt.draw();
		}

		for (auto& v : pHit.top) {
			pt.setColor(Color::Red);
			pt.setPos(v);
			pt.draw();
		}

		for (auto& v : pHit.bottom) {
			pt.setColor(Color::Red);
			pt.setPos(v);
			pt.draw();
		}
#endif // DEBUG
	}
}