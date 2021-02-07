#include "../include/Player.h"
#include "../include/WindowInfo.h"
#include "../include/Camera.h"
#include "../include/Bullet.h"
#include "../include/TextureManager.h"
#include "../EffectManager.h"
#include "../include/BulletManager.h"
#include "../include/Global.h"
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
			if (Input::getKey(Key::LEFT)) {
				xspeedtime = max(xspeedtime - 0.2f, -1.0f);
			}
			else if (Input::getKey(Key::RIGHT)) {
				xspeedtime = min(xspeedtime + 0.2f, 1.0f);
			}
			else {
				xspeedtime *= 0.9f;
			}

			return xspeedtime;
		}

	}

	namespace {
		// プレイヤーの最大のパラメータ
		static const ActorParameter MaxParameter{ 100.0f, 100.0f, 5.0f, 3.0f, 1.0f };
	}

	// ---------- プレイヤーサウンドクラス ----------

	PlayerAudio::PlayerAudio()
		: _audioList(2)
	{
		_audioList[0].load(global::AudioAsset("se_jump.wav"));
		_audioList[0].setVolume(-3000);
		_audioList[1].load(global::AudioAsset("powerup04.wav"));
		_audioList[1].setVolume(-3000);

	}

	PlayerAudio::~PlayerAudio()
	{
	}

	void PlayerAudio::playAudio(int _index)
	{
		_audioList[_index].setPosition(0);
		_audioList[_index].play();
	}

	void PlayerAudio::stopAudio(int _index)
	{
		_audioList[_index].stop();
	}

	// ---------- プレイヤークラス ----------

	Player::Player()
		: IActor()
		, map()
		, sprite()
		, collider()
		, playerState(PlayerState::Wait)
		, playerBody(MaxParameter)
		, playerAudio()
		, isJump(false)
		, isGround(false)
		, effect(5, 1, 24.0f)
	{
		sprite.setTexture(TextureManager::getTexture("Player"));
		effect.setTexture(TextureManager::getTexture("Effect"));

		// 自身のオブジェクトの名前を決める
		this->name = "Player";
	}

	void Player::onStart()
	{
		this->setActive(true);

		// プレイヤーのパラメータをセット(リセット)する
		playerBody.setParamater(MaxParameter);

		velocity = Vector2::Zero;

		bounds.minPos.setPos(0, 0);
		bounds.maxPos.setPos(32, 32);
		bounds.size.setPos(bounds.maxPos - bounds.minPos);
		bounds.center.setPos(bounds.size.half());
	}

	float frame = 0.f;
	float yPower = 0.0f;
	float time = 0.f;
	bool jumpInput = false;
	bool fall = false;

	void Player::onUpdate()
	{
		if (!this->isActive)
		{
			return;
		}

		if (this->fallScreen(map->getMapSize().y)) {
			death();
		}

		movePlayer();

		shotPlayer();

		playerBody.onUpdate();

		// ----- 座標更新 -----
		this->transform.pos = intersectTileMap();                // 座標を更新
		// 画面外にプレイヤーが出ないようにする
		this->transform.pos.x = clamp(this->transform.pos.x, Camera::minScreenPos().x + 16.0f, Camera::maxScreenPos().x - 16.0f);
		// MN: 10000.0f 画面下の上限
		this->transform.pos.y = clamp(this->transform.pos.y, Camera::minScreenPos().y + 16.0f, 10000.0f);
		Camera::setTarget(this->transform.pos);                  // プレイヤーを追跡するようにカメラに座標を渡す
		auto screen = Camera::toScreenPos(this->transform.pos);  // 座標をスクリーン座標へと変換
		//effect.draw(screen, Vector2{ 1.5f, 1.5f }, 0.0f);
		//EffectManager::getIns()->draw(0, screen, Vector2{ 1.5f, 1.5f });

		// ----- コライダー更新 -----
		collider.update(screen, 32.0f, 32.0f);

		// ----- 描画 -----
		sprite.draw(screen, transform.scale, transform.angle, true, isFlip);

		// ----- デバッグ -----
		debug();
	}

	void Player::setMap(Map* _map)
	{
		map = _map;
	}

	Vector2 Player::intersectTileMap()
	{
		auto nextPos = this->transform.pos + velocity;

		// 判定を行う座標を決める
		float offX{ bounds.center.x / 4.0f - 1.0f };
		float offY{ bounds.center.y / 4.0f - 1.0f };

		// 上下判定用に判定ボックス更新
		bounds.minPos.setPos(this->transform.pos.x - bounds.center.x, nextPos.y - bounds.center.y);
		bounds.maxPos.setPos(this->transform.pos.x + bounds.center.x, nextPos.y + bounds.center.y);

		// -- 下 --
		intersectPoint.bottom[0] = Vector2{ bounds.minPos.x + offX, bounds.maxPos.y + 1.0f };
		intersectPoint.bottom[1] = Vector2{ bounds.maxPos.x - offX, bounds.maxPos.y + 1.0f };

		// -- 上 --
		intersectPoint.top[0]    = Vector2{ bounds.minPos.x + offX, bounds.minPos.y };
		intersectPoint.top[1]    = Vector2{ bounds.maxPos.x - offX, bounds.minPos.y };

		nextPos = verticalIntersect(nextPos);

		// 左右判定用に判定ボックス更新
		bounds.minPos.setPos(nextPos.x - bounds.center.x, this->transform.pos.y - bounds.center.y);
		bounds.maxPos.setPos(nextPos.x + bounds.center.x, this->transform.pos.y + bounds.center.y);

		// -- 右 --
		intersectPoint.right[0] = Vector2{ bounds.maxPos.x , bounds.minPos.y + offY };
		intersectPoint.right[1] = Vector2{ bounds.maxPos.x , bounds.maxPos.y - offY };

		// -- 左 --
		intersectPoint.left[0]  = Vector2{ bounds.minPos.x - 1.0f, bounds.minPos.y + offY };
		intersectPoint.left[1]  = Vector2{ bounds.minPos.x - 1.0f, bounds.maxPos.y - offY };
		
		nextPos = holizontalIntersect(nextPos);

		return nextPos;
	}

	Vector2 Player::verticalIntersect(const Vector2& _nextPos)
	{
		auto nextPos = _nextPos;

		// -- 上との当たり判定 --
		for (int i{ 0 }; i < IntersectPoint::Size; ++i) {
			auto mapID = map->getTile((int)intersectPoint.top[i].x / 32, (int)intersectPoint.top[i].y / 32);

			if (mapID == MapTile::BLOCK) {
				auto hitPos = ((int)intersectPoint.top[i].y / MapInfo::MapSize + 1) * (float)MapInfo::MapSize;

				if (intersectPoint.top[i].y <= hitPos) {
					nextPos.y = nextPos.y + fabsf(intersectPoint.top[i].y - hitPos);

					break;
				}
			}
		}

		// -- 下との当たり判定 --
		for (int i{ 0 }; i < IntersectPoint::Size; ++i) {
			auto mapID = map->getTile((int)intersectPoint.bottom[i].x / 32, (int)intersectPoint.bottom[i].y / 32);

			if (mapID == MapTile::BLOCK) {
				auto hitPos = (int)(intersectPoint.bottom[i].y / MapInfo::MapSize) * (float)MapInfo::MapSize;

				if (intersectPoint.bottom[i].y >= hitPos) {
					nextPos.y = nextPos.y - fabsf(intersectPoint.bottom[i].y - hitPos) + 1.0f;

					// 地面についているとき
					isGround = true;

					break;
				}
			}
			else if(mapID == MapTile::OBJECT){
				auto aaa = this->transform.pos.y - nextPos.y;
				if (aaa <= 0) {
					auto hitPos = (int)(intersectPoint.bottom[i].y / MapInfo::MapSize) * (float)MapInfo::MapSize;

					if (intersectPoint.bottom[i].y >= hitPos) {
						nextPos.y = nextPos.y - fabsf(intersectPoint.bottom[i].y - hitPos) + 1.0f;

						// 地面についているとき
						isGround = true;

						break;
					}
				}

			}
			else {
				// 下にマップチップがないとき
				isGround = false;
			}
		}

		return nextPos;
	}

	Vector2 Player::holizontalIntersect(const Vector2& _nextPos)
	{
		auto nextPos = _nextPos;

		// -- 右との当たり判定 --
		for (int i{ 0 }; i < IntersectPoint::Size; ++i) {
			auto mapID = map->getTile((int)intersectPoint.right[i].x / 32, (int)intersectPoint.right[i].y / 32);

			if (mapID == MapTile::BLOCK) {
				float hitPos = (int)(intersectPoint.right[i].x / MapInfo::MapSize) * (float)MapInfo::MapSize;

				if (intersectPoint.right[i].x >= hitPos) {
					nextPos.x = nextPos.x - fabsf(intersectPoint.right[i].x - hitPos);
					break;
				}
			}
		}

		// -- 左との当たり判定 --		
		for (int i{ 0 }; i < IntersectPoint::Size; ++i) {
			auto mapID = map->getTile((int)intersectPoint.left[i].x / 32, (int)intersectPoint.left[i].y / 32);

			if (mapID == MapTile::BLOCK) {
				float hitPos = ((int)intersectPoint.left[i].x / MapInfo::MapSize + 1) * (float)MapInfo::MapSize;

				if (intersectPoint.left[i].x <= hitPos) {
					nextPos.x = nextPos.x + fabsf(intersectPoint.left[i].x - hitPos) - 1.0f;
					break;
				}
			}
		}

		return nextPos;
	}

	void Player::resetPosition(const Vector2& _pos)
	{
		this->setActive(true);
		this->transform.setPos(_pos);
	}

	BoxCollider& Player::getCollider()
	{
		return collider;
	}

	PlayerBody& Player::getPlayerBody()
	{
		return playerBody;
	}

	void Player::death()
	{
		isActive = false;
	}

	void Player::respawn(const Vector2& _pos)
	{
		// velocityを0にする
		this->velocity = Vector2::Zero;

		PlayerInput::xspeedtime = 0.0f;

		isGround = true;

		// パラメータをもとに戻す
		playerBody.setParamater(MaxParameter);

		this->transform.setPos(_pos);

		isActive = true;
	}

	void Player::movePlayer()
	{
		// ----- 移動 -----
		velocity.x = PlayerInput::getinertia() * PlayerParameters::Speed * Time::deltaTime();

		// ----- ジャンプ -----

		jumpInput = Input::getKeyDown(Key::Z);

		// ジャンプキーが押された時
		if (jumpInput) {
			// 地面に足がついているとき
			if (isGround) {
				playerAudio.playAudio(0);
				isGround = false;
				isJump = true;
				fall = true;
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
			fall = true;
			yPower += PlayerParameters::Gravity;
			yPower = min(yPower, PlayerParameters::MaxGravity);
		}

		// 地面に足がついているとき、地面にめり込まないようにする
		if (isGround) {
			fall = false;
			yPower = 0.0f;
		}

		velocity.y = yPower;
	}

	void Player::shotPlayer()
	{
		if (Input::getKeyDown(Key::X)) {

			if (playerBody.getParameter().mp <= 0) {
				return;
			}

			playerAudio.playAudio(1);

			float vx = (velocity.x > 0) ? 10.0f : -10.0f;
			BulletPtr bulletPtr(new Bullet(this->transform.pos, Vector2{ vx, 0.0f }, BulletType::Player));
			bulletPtr->onStart();
			bulletPtr->setAttack(playerBody.getParameter().attack);
			BulletManager::getIns()->addBullet(bulletPtr);
			playerBody.subMp(2.0f);
		}
	}

	void Player::debug()
	{	
		Debug::drawFormatText(0, 40,   Color::Black, "Position = %s", this->transform.pos.toString().c_str());
		Debug::drawFormatText(0, 60,   Color::Black, "Velocity = %s", velocity.toString().c_str());
		Debug::drawFormatText(0, 80,   Color::Black, "isGround = %d", isGround);
		Debug::drawFormatText(0, 100, Color::Black, "isJump   = %d", isJump);
		Debug::drawFormatText(0, 120,  Color::Black, "fall   = %d", fall);
	}
	
}