#include "../include/Player.h"
#include "../include/WindowInfo.h"
#include "../include/Camera.h"
#include "../include/TextureManager.h"
#include "../include/BulletManager.h"
#include <cmath>

namespace gnGame {

	// プレイヤーの重力や速さなどのパラメータ
	namespace PlayerParameters {
		// プレイヤーにかかる重力
		constexpr float Gravity = 0.980f;

		// 最大の重力
		constexpr float MaxGravity = Gravity * 10.0f;

		// プレイヤーが進む速さ
		constexpr float Speed = 350.0f;

		// プレイヤーのジャンプ力
		constexpr float JumpPower = -7.0f;
	};

	// プレイヤーが移動するときに入力される値
	namespace PlayerInput {

		static float xspeedtime = 0;

		float getinertia() {
			if (Input::getKey(Key::A) || Input::getKey(Key::LEFT)) {
				xspeedtime = max(xspeedtime - 0.2f, -1.0f);
			}
			else if (Input::getKey(Key::D) || Input::getKey(Key::RIGHT)) {
				xspeedtime = min(xspeedtime + 0.2f, 1.0f);
			}
			else {
				xspeedtime *= 0.9f;
			}

			return xspeedtime;
		}

	}

	PlayerMoveInfo::PlayerMoveInfo()
		: isJump(false)
		, isSecondJump(false)
		, isGround(false)
	{
	}

	// ---------- プレイヤークラス ----------

	Player::Player()
		: IActor()
		, map()
		, sprite()
		, boxCollider()
		, isJump(false)
		, isGround(false)
		, pt()
	{
	}

	void Player::onStart()
	{
		sprite.setTexture(TextureManager::getTexture("Player"));

		// 自身のオブジェクトの名前を決める
		this->name = "Player";

		// -- 座標初期化 --
		this->transform.pos.setPos(75, 350);

		bounds.minPos.setPos(0, 0);
		bounds.maxPos.setPos(32, 32);
		bounds.size.setPos(bounds.maxPos - bounds.minPos);
		bounds.center.setPos(bounds.size.half());
	}

	float frame = 0.f;
	float yPower = 0.0f;
	float time = 0.f;
	bool jumpInput = false;
	float angle = 0.0f;
	int index = 0;

	void Player::onUpdate()
	{
		if (!this->isActive)
		{
			return;
		}

		resetPosition();

		movePlayer();

		shotPlayer();

		// ----- 座標更新 -----
		this->transform.pos = intersectTileMap();                // 座標を更新
		Camera::setTarget(this->transform.pos);                  // プレイヤーを追跡するようにカメラに座標を渡す
		auto screen = Camera::toScreenPos(this->transform.pos);  // 座標をスクリーン座標へと変換

		// ----- コライダー更新 -----
		boxCollider.update(screen, 32.0f, 32.0f);

		// ----- 描画 -----
		sprite.draw(screen, transform.scale, transform.angle);

		// ----- デバッグ -----
		debug();
	}

	void Player::setMap(Map& _map)
	{
		map = _map;
	}

	Vector2 Player::intersectTileMap()
	{
		auto nextPos = this->transform.pos + velocity;

		// 判定を行う座標を決める
		float offX{ bounds.center.x / 4.0f - 1.0f };
		float offY{ bounds.center.y / 4.0f - 1.0f };

		// 上下判定用のに判定ボックス更新
		bounds.minPos.setPos(this->transform.pos.x - bounds.center.x, nextPos.y - bounds.center.y);
		bounds.maxPos.setPos(this->transform.pos.x + bounds.center.x, nextPos.y + bounds.center.y);

		// -- 下 --
		intersectPoint.bottom[0] = Vector2{ bounds.minPos.x + offX, bounds.maxPos.y + 1.0f };
		intersectPoint.bottom[1] = Vector2{ bounds.maxPos.x - offX, bounds.maxPos.y + 1.0f };

		// -- 上 --
		intersectPoint.top[0]    = Vector2{ bounds.minPos.x + offX, bounds.minPos.y - 1.0f };
		intersectPoint.top[1]    = Vector2{ bounds.maxPos.x - offX, bounds.minPos.y - 1.0f };

		// -- 上との当たり判定 --
		for (int i{}; i < IntersectPoint::Size; ++i) {

			if (map.checkTile((int)intersectPoint.top[i].x, (int)intersectPoint.top[i].y)) {
				auto hitPos = ((int)intersectPoint.top[i].y / MapInfo::MapSize + 1) * (float)MapInfo::MapSize;

				if (intersectPoint.top[i].y <= hitPos) {
					nextPos.y = nextPos.y + fabsf(intersectPoint.top[i].y - hitPos);

					break;
				}
			}
		}

		// -- 下との当たり判定 --
		for (int i{}; i < IntersectPoint::Size; ++i) {

			if (map.checkTile((int)intersectPoint.bottom[i].x, (int)intersectPoint.bottom[i].y)) {
				auto hitPos = (int)(intersectPoint.bottom[i].y / MapInfo::MapSize) * (float)MapInfo::MapSize;

				if (intersectPoint.bottom[i].y >= hitPos) {
					nextPos.y = nextPos.y - fabsf(intersectPoint.bottom[i].y - hitPos) + 1.0f;

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
		bounds.minPos.setPos(nextPos.x - bounds.center.x, this->transform.pos.y - bounds.center.y);
		bounds.maxPos.setPos(nextPos.x + bounds.center.x, this->transform.pos.y + bounds.center.y);

		// -- 右 --
		intersectPoint.right[0] = Vector2{ bounds.maxPos.x , bounds.minPos.y + offY };
		intersectPoint.right[1] = Vector2{ bounds.maxPos.x , bounds.maxPos.y - offY };

		// -- 左 --
		intersectPoint.left[0]  = Vector2{ bounds.minPos.x - 1.0f, bounds.minPos.y + offY };
		intersectPoint.left[1]  = Vector2{ bounds.minPos.x - 1.0f, bounds.maxPos.y - offY };
		

		// -- 右との当たり判定 --
		for (int i{}; i < IntersectPoint::Size; ++i) {

			if (map.checkTile((int)intersectPoint.right[i].x, (int)intersectPoint.right[i].y)) {
				float hitPos = (int)(intersectPoint.right[i].x / MapInfo::MapSize) * (float)MapInfo::MapSize;

				if (intersectPoint.right[i].x >= hitPos) {
					nextPos.x = nextPos.x - fabsf(intersectPoint.right[i].x - hitPos);

					break;
				}
			}
		}

		// -- 左との当たり判定 --		
		for (int i{}; i < IntersectPoint::Size; ++i) {

			if (map.checkTile((int)intersectPoint.left[i].x, (int)intersectPoint.left[i].y)) {
				float hitPos = ((int)intersectPoint.left[i].x / MapInfo::MapSize + 1) * (float)MapInfo::MapSize;

				if (intersectPoint.left[i].x <= hitPos) {
					nextPos.x = nextPos.x + fabsf(intersectPoint.left[i].x - hitPos) - 1.0f;
					break;
				}
			}
		}

		return nextPos;
	}

	void Player::resetPosition()
	{
		if (Input::getKey(Key::R)) {
			this->transform.pos.setPos(0.0f, 0.0f);
		}
	}

	BoxCollider& Player::getCollider()
	{
		return boxCollider;
	}

	void Player::movePlayer()
	{
		// ----- 移動 -----
		velocity.x = PlayerInput::getinertia() * PlayerParameters::Speed * Time::deltaTime();

		// ----- ジャンプ -----

		jumpInput = Input::getKey(Key::SPACE);

		// ジャンプキーが押された時
		if (jumpInput) {
			// 地面に足がついているとき
			if (isGround) {
				isGround = false;
				isJump = true;
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
			yPower = PlayerParameters::JumpPower * time;
		}
		else {
			yPower += PlayerParameters::Gravity;
			yPower = min(yPower, PlayerParameters::MaxGravity);
		}

		// 地面に足がついているとき、地面にめり込まないようにする
		if (isGround) {
			yPower = 0.0f;
		}

		velocity.y = yPower;
	}

	void Player::shotPlayer()
	{
		angle += 0.01f;
		if (Input::getKeyDown(Key::L)) {
			float vx = (velocity.x > 0) ? 10.0f : -10.0f;
			BulletPtr bulletPtr(new Bullet(this->transform.pos, Vector2{ vx, 0.0f }, BulletType::Player));
			bulletPtr->onStart();
			BulletManager::getIns()->addBullet(bulletPtr);
		}
	}

	void Player::debug()
	{
#ifndef DEBUG
		
		/*
		Debug::drawFormatText(0, 40,   Color::Black, "Position = %s", this->transform.pos.toString().c_str());
		Debug::drawFormatText(0, 60,   Color::Black, "Velocity = %s", velocity.toString().c_str());
		Debug::drawFormatText(0, 80,   Color::Black, "isGround = %d", isGround);
		Debug::drawFormatText(0, 100,  Color::Black, "isJump   = %d", isJump);
		*/

		/*
		Debug::drawLine(bounds.minPos, Vector2{ bounds.minPos.x, bounds.maxPos.y }, 2.f, Color::Green);
		Debug::drawLine(bounds.minPos, Vector2{ bounds.maxPos.x, bounds.minPos.y }, 2.f, Color::Green);
		Debug::drawLine(Vector2{ bounds.maxPos.x, bounds.minPos.y }, bounds.maxPos, 2.f, Color::Green);
		Debug::drawLine(Vector2{ bounds.minPos.x, bounds.maxPos.y }, bounds.maxPos, 2.f, Color::Green);
		*/

		/*
		for (auto& v : intersectPoint.right) {
			pt.setColor(Color::Red);
			pt.setPos(v);
			pt.draw();
		}

		for (auto& v : intersectPoint.left) {
			pt.setColor(Color::Red);
			pt.setPos(v);
			pt.draw();
		}

		for (auto& v : intersectPoint.top) {
			pt.setColor(Color::Red);
			pt.setPos(v);
			pt.draw();
		}

		for (auto& v : intersectPoint.bottom) {
			pt.setColor(Color::Red);
			pt.setPos(v);
			pt.draw();
		}
		*/

#endif // DEBUG
	}
}