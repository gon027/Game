#include "Player.h"
#include "WindowInfo.h"
#include <cmath>

namespace gnGame {

	namespace PlayerInfo {
		// プレイヤーにかかる重力
		constexpr float Gravity = 0.98f;

		// プレイヤーが進む速さ
		constexpr float Speed = 5.0f;

		// プレイヤーのジャンプ力
		constexpr float JumpPower = -7.0f;


		// プレイヤーの進む距離
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
		// -- 座標初期化 --
		pos.setPos(100, 350);

		bounds.minPos.setPos(0, 0);
		bounds.maxPos.setPos(32, 32);
		bounds.size.setPos(bounds.maxPos - bounds.minPos);
		bounds.center.setPos(bounds.size.half());
	}

	int frame = 0;

	void Player::onUpdate()
	{
		// ----- 移動 -----
		velocity.x = PlayerInfo::getAxis() * PlayerInfo::Speed;
		
		// ジャンプキーが押された時
		if (Input::getKeyDown(Key::SPACE)) {
			velocity.y = 5.f;

			// 地面に足がついているとき
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

		// ----- 移動判定 -----

		int size = 2;

		// -- 右(-) --
		pHit.right[0] = Vector2{ bounds.maxPos.x, bounds.minPos.y + 8 };
		pHit.right[1] = Vector2{ bounds.maxPos.x, bounds.minPos.y + 24 };

		for (int i{}; i < size; ++i) {
			if (map.getTile((int)pHit.right[i].x / 32, (int)pHit.right[i].y / 32) == MAP_TILE(2)
				|| pHit.right[i].x >= WindowInfo::WindowWidth) {

				// あたったときにvelocityを加算ベクトルを求める
				float nextRightPos = pHit.right[i].x + velocity.x;

				// あたった場所を求める
				float r = pHit.right[i].x / 32 * 32;

				// 押し戻す
				// * Posを直接いじるのではなく、velocityに操作させるほうがいいかも
				pos.x = pos.x - fabsf(nextRightPos - r);

				break;
			}
		}

		// -- 左(+) --
		pHit.left[0] = Vector2{ bounds.minPos.x, bounds.minPos.y + 8 };
		pHit.left[1] = Vector2{ bounds.minPos.x, bounds.minPos.y + 24 };

		for (int i{}; i < size; ++i) {
			if (map.getTile((int)pHit.left[i].x / 32, (int)pHit.left[i].y / 32) == MAP_TILE(2)
				|| pHit.left[i].x <= 0) {
				// あたったときにvelocityを加算ベクトルを求める
				float nextRightPos = pHit.left[i].x + velocity.x;

				// あたった場所を求める
				float r = pHit.left[i].x / 32 * 32;

				// 押し戻す
				// * Posを直接いじるのではなく、velocityに操作させるほうがいいかも
				pos.x = pos.x + fabsf(nextRightPos - r);

				break;
			}
		}

		// -- 上(+) --
		pHit.top[0] = Vector2{ bounds.minPos.x + 8,  bounds.minPos.y };
		pHit.top[1] = Vector2{ bounds.minPos.x + 24, bounds.minPos.y };

		for (int i{}; i < size; ++i) {
			if (map.getTile((int)pHit.top[i].x / 32, (int)pHit.top[i].y / 32) == MAP_TILE(2)
				|| pHit.top[i].y <= 0.0f) {

				// あたったときにvelocityを加算ベクトルを求める
				auto nextRightPos = pHit.top[i].y + velocity.y;

				// あたった場所を求める
				auto r = pHit.top[i].y / 32 * 32;

				// 押し戻す
				pos.y = pos.y + fabsf(nextRightPos - r);

				break;
			}
		}

		// -- 下(-) --
		pHit.bottom[0] = Vector2{ bounds.minPos.x + 8,  bounds.maxPos.y };
		pHit.bottom[1] = Vector2{ bounds.minPos.x + 24, bounds.maxPos.y };

		for (int i{}; i < size; ++i) {
			if (map.getTile((int)pHit.bottom[i].x / 32, (int)pHit.bottom[i].y / 32) == MAP_TILE(2)
				|| pHit.bottom[i].y >= WindowInfo::WindowHeight) {

				// あたったときにvelocityを加算ベクトルを求める
				auto nextRightPos = pHit.bottom[i].y + velocity.y;

				// あたった場所を求める
				auto r = pHit.bottom[i].y / 32 * 32;

				// 押し戻す
				pos.y = pos.y - fabsf(nextRightPos - r);

				isGround = true;

				break;
			}
		}

		// ----- 座標更新 -----
		pos += velocity;

		// 判定ボックス更新
		bounds.minPos.setPos(pos.x - bounds.center.x, pos.y - bounds.center.y);
		bounds.maxPos.setPos(32 + pos.x - bounds.center.x, 32 + pos.y - bounds.center.y);

		pImage.sprite.setPos(pos);

		// ----- 描画 -----
		pImage.sprite.draw();

		// ----- デバッグ -----
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