#include "Player.h"
#include "WindowInfo.h"
#include "Camera.h"
#include <cmath>

#define F .f

namespace gnGame {

	namespace PlayerInfo {
		// プレイヤーにかかる重力
		constexpr float Gravity = 0.98f;

		// プレイヤーが進む速さ
		constexpr float Speed = 5.0f;

		// プレイヤーのジャンプ力
		constexpr float JumpPower = -7.0f;

		float xspeedtime = 0;

		// プレイヤーの進む距離
		float getAxis() {
			float r = 0.0f;
			if (Input::getKey(Key::A) || Input::getKey(Key::LEFT)) {
				r -= 1.0f;
			}

			if (Input::getKey(Key::D) || Input::getKey(Key::RIGHT)) {
				r += 1.0f;
			}

			return r;
		}

		float getAxisY() {
			float r = 0.0f;
			if (Input::getKey(Key::DOWN)) {
				r += 1.0f;
			}
			
			if (Input::getKey(Key::UP)) {
				r -= 1.0f;
			}

			return r;
		}

	};

	PlayerImage::PlayerImage()
		: texture("Image/Test_Player.png")
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
		// -- 座標初期化 --
		pos.setPos(75, 350);

		bounds.minPos.setPos(0, 0);
		bounds.maxPos.setPos(32, 32);
		bounds.size.setPos(bounds.maxPos - bounds.minPos);
		bounds.center.setPos(bounds.size.half());
	}

	float frame = 0.f;
	float yPower = 0.0f;
	float time = 0.f;
	bool jumpInput = false;
	Vector2 screen;

	void Player::onUpdate()
	{
		resetPosition();
		
		// ----- 移動 -----
		velocity.x = PlayerInfo::getAxis() * PlayerInfo::Speed;
		//velocity.y = PlayerInfo::getAxisY() * 5.0f;

		
		// ----- ジャンプ -----

		jumpInput = Input::getKey(Key::SPACE);

		// ジャンプキーが押された時
		if (jumpInput) {
			// 地面に足がついているとき
			if (isGround) {
				isGround = false;
				isJump   = true;
				time = 0.0f;
			}
		}

		// 空中にいるとき
		if (isJump) {
			if (time >= 1.0f) {
				time = 1.0f;
				isJump = false;
				frame = 0;
				jumpInput = false;
			}

			time += 0.16f;
			yPower = PlayerInfo::JumpPower * time;
		}
		else {
			yPower += PlayerInfo::Gravity;
		}

		// 地面に足がついているとき、地面にめり込まないようにする
		if (isGround) {
			yPower = 0.0f;
		}

		velocity.y = yPower;
		
		check();

		// ----- 描画 -----
		pImage.sprite.draw();

		// ----- デバッグ -----
		debug();
	}

	void Player::setMap(Map& _map)
	{
		map = _map;
	}

	bool Player::checkTile(int _x, int _y) {
		auto tile = map.getTile(_x / 32, _y / 32);

		switch (tile)
		{
		case gnGame::MapTile::NONE:
			return false;
			break;
		case gnGame::MapTile::BLOCK:
			return true;
			break;
		case gnGame::MapTile::OBJECT:
			return true;
			break;
		default:
			return false;
			break;
		}

		return false;
	}

	void Player::check()
	{
		// ----- 移動判定 -----

		auto nextPos = pos + velocity;

		// 判定を行う座標を更新
		float offX{ bounds.center.x / 4.0f - 1.0f };
		float offY{ bounds.center.y / 4.0f - 1.0f };

		// 上下判定用のに判定ボックス更新
		bounds.minPos.setPos(pos.x - bounds.center.x, nextPos.y - bounds.center.y);
		bounds.maxPos.setPos(pos.x + bounds.center.x, nextPos.y + bounds.center.y);

		// -- 下 --
		pHit.bottom[0] = Vector2{ bounds.minPos.x + offX, bounds.maxPos.y + 1.0f };
		pHit.bottom[1] = Vector2{ bounds.maxPos.x - offX, bounds.maxPos.y + 1.0f };

		// -- 上 --
		pHit.top[0]    = Vector2{ bounds.minPos.x + offX, bounds.minPos.y - 1.0f };
		pHit.top[1]    = Vector2{ bounds.maxPos.x - offX, bounds.minPos.y - 1.0f };

		// -- 上(+)との当たり判定 --
		for (int i{}; i < PlayerHit::Size; ++i) {

			if (checkTile((int)pHit.top[i].x, (int)pHit.top[i].y)) {

				// あたった場所を求める
				auto hitPos = ((int)pHit.top[i].y / 32 + 1) * 32.0f;

				if (pHit.top[i].y <= hitPos) {
					nextPos.y = nextPos.y + fabsf(pHit.top[i].y - hitPos) - 1.0f;

					break;
				}
			}
		}

		// -- 下(-)との当たり判定 --
		for (int i{}; i < PlayerHit::Size; ++i) {

			if (checkTile((int)pHit.bottom[i].x, (int)pHit.bottom[i].y)) {

				// あたった場所を求める
				auto hitPos = (int)(pHit.bottom[i].y / 32) * 32.0f;

				if (pHit.bottom[i].y >= hitPos) {
					nextPos.y = nextPos.y - fabsf(pHit.bottom[i].y - hitPos) + 1.0f;

					// 地面についているとき
					isGround = true;

					break;
				}
			}
			else {
				// 下にマップチップがないとき
				isGround = false;
			}
		}

		// 左右判定用に判定ボックス更新
		bounds.minPos.setPos(nextPos.x - bounds.center.x, pos.y - bounds.center.y);
		bounds.maxPos.setPos(nextPos.x + bounds.center.x, pos.y + bounds.center.y);

		// -- 右 --
		pHit.right[0] = Vector2{ bounds.maxPos.x , bounds.minPos.y + offY };
		pHit.right[1] = Vector2{ bounds.maxPos.x , bounds.maxPos.y - offY };

		// -- 左 --
		pHit.left[0]  = Vector2{ bounds.minPos.x - 1.0f, bounds.minPos.y + offY };
		pHit.left[1]  = Vector2{ bounds.minPos.x - 1.0f, bounds.maxPos.y - offY };
		

		// -- 右(-)との当たり判定 --
		for (int i{}; i < PlayerHit::Size; ++i) {

			if (checkTile((int)pHit.right[i].x, (int)pHit.right[i].y)) {
				float hitPos = (int)(pHit.right[i].x / 32) * 32.0f;

				if (pHit.right[i].x >= hitPos) {
					nextPos.x = nextPos.x - fabsf(pHit.right[i].x - hitPos) + 1.0f;

					break;
				}
			}
		}

		// -- 左(+)との当たり判定 --		
		for (int i{}; i < PlayerHit::Size; ++i) {

			if (checkTile((int)pHit.left[i].x, (int)pHit.left[i].y)) {
				float hitPos = ((int)pHit.left[i].x / 32 + 1) * 32.0f;

				if (pHit.left[i].x <= hitPos) {
					nextPos.x = nextPos.x + fabsf(pHit.left[i].x - hitPos) - 1.0f;
					break;
				}
			}
		}

		// ----- 座標更新 -----
		pos = nextPos;
		camera->setTarget(pos);
		screen = camera->toScreenPos(pos);
		pImage.sprite.setPos(screen);
	}

	const Vector2& Player::getPos()
	{
		return pos;
	}

	const Vector2& Player::getVelocity()
	{
		return velocity;
	}

	void Player::resetPosition()
	{
		if (Input::getKey(Key::R)) {
			pos.setPos(0.0f, 0.0f);
		}
	}

	void Player::debug()
	{
#ifndef DEBUG
		
		Debug::drawFormatText(0, 20,  Color::Black, "Position = %s", pos.toString().c_str());
		Debug::drawFormatText(0, 40,  Color::Black, "Velocity = %s", velocity.toString().c_str());
		Debug::drawFormatText(0, 60,  Color::Black, "isGround = %d", isGround);
		Debug::drawFormatText(0, 80,  Color::Black, "isJump   = %d", isJump);
		Debug::drawFormatText(0, 100, Color::Black, "MapChip  = %d %d", (int)pHit.top[0].x / 32, (int)pHit.top[0].y / 32);
		Debug::drawFormatText(0, 120, Color::Black, "MapChip  = %d", map.getTile((int)pHit.top[0].x / 32, (int)pHit.top[0].y / 32));

		/*
		Debug::drawLine(bounds.minPos, Vector2{ bounds.minPos.x, bounds.maxPos.y }, 2.f, Color::Green);
		Debug::drawLine(bounds.minPos, Vector2{ bounds.maxPos.x, bounds.minPos.y }, 2.f, Color::Green);
		Debug::drawLine(Vector2{ bounds.maxPos.x, bounds.minPos.y }, bounds.maxPos, 2.f, Color::Green);
		Debug::drawLine(Vector2{ bounds.minPos.x, bounds.maxPos.y }, bounds.maxPos, 2.f, Color::Green);
		*/

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