#include "Player.h"
#include "WindowInfo.h"
#include "Camera.h"
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

	Player::Player(Camera* _camera, Map& _map)
		: camera(_camera)
		, map(_map)
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
		pos.setPos(75, 350);

		bounds.minPos.setPos(0, 0);
		bounds.maxPos.setPos(32, 32);
		bounds.size.setPos(bounds.maxPos - bounds.minPos);
		bounds.center.setPos(bounds.size.half());
	}

	float frame = 0.f;
	Vector2 screen;

	void Player::onUpdate()
	{
		if (Input::getKeyDown(Key::R)) {
			pos.setPos(0.f, 0.f);
		}
		
		// ----- �ړ� -----
		velocity.x = PlayerInfo::getAxis() * PlayerInfo::Speed;
		//velocity.y = PlayerInfo::getAxisY() * PlayerInfo::Speed;
		
		
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
			velocity.y = PlayerInfo::Gravity * 5.f;
		}

		// ----- �ړ����� -----

		// ����{�b�N�X�X�V
		bounds.minPos.setPos(pos.x - bounds.center.x, pos.y - bounds.center.y);
		bounds.maxPos.setPos(pos.x + bounds.center.x, pos.y + bounds.center.y);

		// ������s�����W���X�V
		float offX{ bounds.center.x / 4.0f + 2.0f };
		float offY{ bounds.center.y / 4.0f + 2.0f };

		// -- �E --
		pHit.right[0]  = Vector2{ bounds.maxPos.x, bounds.minPos.y + offY };
		pHit.right[1]  = Vector2{ bounds.maxPos.x, bounds.maxPos.y - offY };

		// -- �� --
		pHit.left[0]   = Vector2{ bounds.minPos.x, bounds.minPos.y + offY };
		pHit.left[1]   = Vector2{ bounds.minPos.x, bounds.maxPos.y - offY };

		// -- �� --
		pHit.bottom[0] = Vector2{ bounds.minPos.x + offX, bounds.maxPos.y };
		pHit.bottom[1] = Vector2{ bounds.maxPos.x - offX, bounds.maxPos.y };

		// -- �� --
		pHit.top[0]    = Vector2{ bounds.minPos.x + offX, bounds.minPos.y };
		pHit.top[1]    = Vector2{ bounds.maxPos.x - offX, bounds.minPos.y };

		// -- �E(-)�Ƃ̓����蔻�� --
		for (int i{}; i < PlayerHit::Size; ++i) {

			auto tile = map.getTile((int)pHit.right[i].x / 32, (int)pHit.right[i].y / 32);

			if (tile == MAP_TILE(2)) {
				// ���������Ƃ���velocity�����Z�x�N�g�������߂�
				float nextRightPos = pHit.right[i].x + velocity.x;

				// ���������ꏊ�����߂�
				float hitPos = (int)(pHit.right[i].x / 32) * 32.f;

				// �����߂�
				pos.x = pos.x - fabsf(nextRightPos - hitPos);

				break;
			}
		}

		// -- ��(+)�Ƃ̓����蔻�� --		
		for (int i{}; i < PlayerHit::Size; ++i) {

			auto tile = map.getTile((int)pHit.left[i].x / 32, (int)pHit.left[i].y / 32);

			if (tile == MAP_TILE(2)) {
				// �ړ���̍��W�����߂�
				float nextLeftPos = pHit.left[i].x + velocity.x;  // 32 - 5 => 22

				// ���������ꏊ�����߂�
				float hitPos = ((int)pHit.left[i].x / 32 + 1) * 32.f;

				Debug::drawFormatText(0, 220, Color::Black, "nextLeftPos = %f", nextLeftPos);
				Debug::drawFormatText(0, 240, Color::Black, "sub = %f", fabsf(nextLeftPos - hitPos));
				Debug::drawFormatText(0, 260, Color::Black, "bounds = %f", bounds.minPos.x);
				Debug::drawFormatText(0, 280, Color::Black, "left = %f", pHit.left[i].x);
				Debug::drawFormatText(0, 300, Color::Black, "vel = %f", velocity.x);

				// �����߂�
				pos.x = pos.x + fabsf(nextLeftPos - hitPos) - 1.0f;

				break;
			}
		}
		
		// -- ��(+)�Ƃ̓����蔻�� --
		for (int i{}; i < PlayerHit::Size; ++i) {

			auto tile = map.getTile((int)pHit.top[i].x / 32, (int)pHit.top[i].y / 32);

			if (tile == MAP_TILE(2)) {
				// ���������Ƃ���velocity�����Z�x�N�g�������߂�
				auto nextTopPos = pHit.top[i].y + velocity.y;

				// ���������ꏊ�����߂�
				auto hitPos = ((int)pHit.top[i].y / 32 + 1) * 32.f;

				// �����߂�
				pos.y = pos.y + fabsf(nextTopPos - hitPos) - 0.1f;

				break;
			}
		}		

		// -- ��(-)�Ƃ̓����蔻�� --
		for (int i{}; i < PlayerHit::Size; ++i) {

			auto tile = map.getTile((int)pHit.bottom[i].x / 32, (int)pHit.bottom[i].y / 32);

			if (tile == MAP_TILE(2)) {

				// ���������Ƃ���velocity�����Z�x�N�g�������߂�
				auto nextBottomPos = pHit.bottom[i].y + velocity.y;

				// ���������ꏊ�����߂�
				auto hitPos = (int)pHit.bottom[i].y / 32 * 32.f;

				// �����߂�
				pos.y = pos.y - fabsf(nextBottomPos - hitPos);

				isGround = true;

				break;
			}
		}
		
		// ----- ���W�X�V -----
		pos += velocity;
		camera->setTarget(pos);
		screen = camera->toScreenPos(pos);
		pImage.sprite.setPos(screen);

		// ----- �`�� -----
		pImage.sprite.draw();

		// ----- �f�o�b�O -----
		debug();
	}

	void Player::setMap(Map& _map)
	{
		map = _map;
	}

	const Vector2& Player::getPos()
	{
		return pos;
	}

	const Vector2& Player::getVelocity()
	{
		return velocity;
	}

	void Player::debug()
	{
#ifndef DEBUG
		Debug::drawFormatText(0, 20,  Color::Black, "Position = %s", pos.toString().c_str());
		Debug::drawFormatText(0, 40,  Color::Black, "Screen   = %s", screen.toString().c_str());
		Debug::drawFormatText(0, 60,  Color::Black, "Velocity = %s", velocity.toString().c_str());
		Debug::drawFormatText(0, 80,  Color::Black, "isGround = %d", isGround);
		Debug::drawFormatText(0, 100, Color::Black, "isJump   = %d", isJump);
		Debug::drawFormatText(0, 120, Color::Black, "frame    = %d", frame);
		Debug::drawFormatText(0, 140, Color::Black, "Block    = %d", map.getTile((int)screen.x / 32, (int)screen.y / 32));
		Debug::drawFormatText(0, 160, Color::Black, "BlockPos = %d, %d", (int)bounds.maxPos.x / 32, (int)bounds.maxPos.y / 32);

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