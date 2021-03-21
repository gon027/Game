#include "../include/BossState.h"
#include "../include/Lib.h"
#include "../include/Boss.h"
#include "../include/Bullet.h"
#include "../include/BulletManager.h"
#include "../include/Randam.h"
#include "../include/GameScene.h"

namespace gnGame {

	/// <summary>
	/// ボスの移動するときのパラメータ
	/// </summary>
	namespace MoveParams {
		constexpr float MaxMoveTime{ 3.0f };            // 移動時間
		const Vector2 TargetPoint1{ 160.0f , 336.0f };   // BossMove1の移動先
		const Vector2 TargetPoint2{ 618.0f, 336.0f };   // BossMove2の移動先
		float moveTime{ 0.0f };                         // 経過時間 
		float moveRate{ 0.0f };                         // 経過時間を[0.0f, 1.0f]に合わせるための変数

		Vector2 start{ Vector2::Zero };                 // ボスのスタート位置

		// Todo : gnLib::Vector2に追加しておく
		Vector2 leap(const Vector2& _start, const Vector2& _end, float time) {
			return {
				_start.x + (_end.x - _start.x) * time,
				_start.y + (_end.y - _start.y) * time,
			};
		}

		const bool isNearly(const Vector2& _thisPos, const Vector2& _target) {
			const auto nearPos = _target - _thisPos;
			return nearPos.x < 0.01f && nearPos.y < 0.01f;
		}
	}

	// ボスの攻撃時間
	namespace BossAttackTime {
		
		constexpr float shotAttack = 5.0f;

		constexpr float shotInterval = 0.75f;
	}

	// ---------- BossWait ----------
	BossAction::BossWait::BossWait(float waitTime)
		: waitTime(0.0f)
		, maxWaitTime(waitTime)
	{
	}

	void BossAction::BossWait::update(Boss* _boss)
	{
		waitTime += Time::deltaTime();
		
		if (waitTime >= maxWaitTime) {
			auto rand = static_cast<BossPattern>(Randam::getRandomRange(1, 8));
			_boss->changeState(rand);
		}
	}

	// ---------- BossMoveRight ----------
	BossAction::BossMoveRight::BossMoveRight(Boss* _boss)
	{
		MoveParams::moveTime = 0.0f;
		MoveParams::moveRate = 0.0f;

		_boss->setDirection(Direction::Left);
		MoveParams::start = _boss->transform.pos;
	}

	void BossAction::BossMoveRight::update(Boss* _boss)
	{
		// 目的の位置まで到着したとき
		if (MoveParams::moveTime >= MoveParams::MaxMoveTime) {
			_boss->setDirection(Direction::Right);
			auto rand = static_cast<BossPattern>(Randam::getRandomRange(0, 8));
			_boss->changeState(rand);
		}
		
		MoveParams::moveRate = MoveParams::moveTime / MoveParams::MaxMoveTime;
		_boss->transform.pos.setPos(
			MoveParams::leap(MoveParams::start, MoveParams::TargetPoint1, MoveParams::moveRate)
		);

		MoveParams::moveTime += Time::deltaTime();
	}

	// ---------- BossMoveLeft ----------
	BossAction::BossMoveLeft::BossMoveLeft(Boss* _boss)
	{
		MoveParams::moveTime = 0.0f;
		MoveParams::moveRate = 0.0f;

		_boss->setDirection(Direction::Right);
		MoveParams::start = _boss->transform.pos;
	}

	void BossAction::BossMoveLeft::update(Boss* _boss)
	{
		// 目的の位置まで到着したとき
		if (MoveParams::moveTime >= MoveParams::MaxMoveTime) {
			_boss->setDirection(Direction::Left);
			auto rand = static_cast<BossPattern>(Randam::getRandomRange(0, 8));
			_boss->changeState(rand);
		}

		MoveParams::moveRate = MoveParams::moveTime / MoveParams::MaxMoveTime;
		_boss->transform.pos.setPos(
			MoveParams::leap(MoveParams::start, MoveParams::TargetPoint2, MoveParams::moveRate)
		);

		MoveParams::moveTime += Time::deltaTime();
	}

	// ---------- BossMoveShotRight ----------
	BossAction::BossMoveShotRight::BossMoveShotRight(Boss* _boss)
		: shotTime(0.0f)
	{
		MoveParams::moveTime = 0.0f;
		MoveParams::moveRate = 0.0f;

		_boss->setDirection(Direction::Left);
		MoveParams::start = _boss->transform.pos;
	}

	void BossAction::BossMoveShotRight::update(Boss* _boss)
	{
		// 目的の位置まで到着したとき
		if (MoveParams::moveTime >= MoveParams::MaxMoveTime) {
			_boss->setDirection(Direction::Right);
			auto rand = static_cast<BossPattern>(Randam::getRandomRange(0, 8));
			_boss->changeState(rand);
		}

		MoveParams::moveRate = MoveParams::moveTime / MoveParams::MaxMoveTime;
		_boss->transform.pos.setPos(
			MoveParams::leap(MoveParams::start, MoveParams::TargetPoint1, MoveParams::moveRate)
		);

		// 0.5秒に1回発射する
		if (shotTime >= 0.5f) {
			shotTime = 0.0f;

			auto direction = Vector2{ -7.0f, 0.0f };
			auto pos = _boss->transform.pos;
			pos.y += 16.0f;
			BulletPtr bullet{ new Bullet{ pos, direction } };
			bullet->onStart();
			bullet->setAttack(_boss->getParameter().attack);
			BulletManager::getIns()->addBullet(bullet);
		}

		MoveParams::moveTime += Time::deltaTime();
		shotTime += Time::deltaTime();
	}

	// ---------- BossMoveShotLeft ----------
	BossAction::BossMoveShotLeft::BossMoveShotLeft(Boss* _boss)
		: shotTime(0.0f)
	{
		MoveParams::moveTime = 0.0f;
		MoveParams::moveRate = 0.0f;

		_boss->setDirection(Direction::Right);
		MoveParams::start = _boss->transform.pos;
	}

	void BossAction::BossMoveShotLeft::update(Boss* _boss)
	{
		// 目的の位置まで到着したとき
		if (MoveParams::moveTime >= MoveParams::MaxMoveTime) {
			_boss->setDirection(Direction::Left);
			auto rand = static_cast<BossPattern>(Randam::getRandomRange(0, 8));
			_boss->changeState(rand);
		}

		MoveParams::moveRate = MoveParams::moveTime / MoveParams::MaxMoveTime;
		_boss->transform.pos.setPos(
			MoveParams::leap(MoveParams::start, MoveParams::TargetPoint2, MoveParams::moveRate)
		);

		// 0.5秒に1回発射する
		if (shotTime >= 0.5f) {
			shotTime = 0.0f;

			auto direction = Vector2{ 7.0f, 0.0f };
			auto pos = _boss->transform.pos;
			pos.y += 16.0f;
			BulletPtr bullet{ new Bullet{ pos, direction } };
			bullet->onStart();
			bullet->setAttack(_boss->getParameter().attack);
			BulletManager::getIns()->addBullet(bullet);
		}

		MoveParams::moveTime += Time::deltaTime();
		shotTime += Time::deltaTime();
	}

	// ---------- TargetPlayerShot ----------
	BossAction::TargetPlayerShot::TargetPlayerShot(GameScene* _gameScene)
		: gameScene(_gameScene)
		, actionTime(0.0f)
		, shotTime(0.0f)
	{
	}

	void BossAction::TargetPlayerShot::update(Boss* _boss)
	{
		actionTime += Time::deltaTime();
		shotTime += Time::deltaTime();

		if (actionTime >= BossAttackTime::shotAttack) {
			auto rand = static_cast<BossPattern>(Randam::getRandomRange(0, 8));
			_boss->changeState(rand);
		}

		if (shotTime >= BossAttackTime::shotInterval) {
			float accel = 7.0f;

			auto playerPos = gameScene->getPlayer()->transform.pos - _boss->transform.pos;
			float angle = atan2f(playerPos.y, playerPos.x);

			auto direction = Vector2{ cosf(angle) * accel, sinf(angle) * accel };
			BulletPtr bullet{ new Bullet{_boss->transform.pos, direction} };
			bullet->onStart();
			bullet->setAttack(_boss->getParameter().attack);
			BulletManager::getIns()->addBullet(bullet);
			accel += 0.2f;

			shotTime = 0.0f;
		}
	}

	// ---------- ScatterShot ----------
	BossAction::ScatterShot::ScatterShot(GameScene* _gameScene)
		: gameScene(_gameScene)
		, actionTime(0.0f)
		, shotTime(0.0f)
	{
	}

	void BossAction::ScatterShot::update(Boss* _boss)
	{
		actionTime += Time::deltaTime();
		shotTime += Time::deltaTime();

		if (actionTime >= BossAttackTime::shotAttack) {
			auto rand = static_cast<BossPattern>(Randam::getRandomRange(0, 8));
			_boss->changeState(rand);
		}
		
		if (shotTime >= BossAttackTime::shotInterval) {
			auto pos = gameScene->getPlayer()->transform.pos - _boss->transform.pos;
			float angle = atan2f(pos.y, pos.x);

			const float r = toRadians(Range);
			const float startAngle = angle - r;
			const float endAngle = angle + r;
			const float inc{ (r * 2) / 5.0f };
			
			// [angle - theta, angle + theta]の範囲分弾を発射する
			for (float rad{ startAngle }; rad < endAngle; rad += inc) {
				auto direction = Vector2{ cosf(rad) * 5.0f, sinf(rad) * 5.0f };
				BulletPtr bullet{ new Bullet{_boss->transform.pos, direction} };
				bullet->onStart();
				bullet->setAttack(_boss->getParameter().attack);
				BulletManager::getIns()->addBullet(bullet);
			}
						
			shotTime = 0.0f;
		}
	}

	// --------- LinearShot ----------
	BossAction::LinearShot::LinearShot()
		: actionTime(0.0f)
		, shotTime(0.0f)
	{
	}

	void BossAction::LinearShot::update(Boss* _boss)
	{
		actionTime += Time::deltaTime();
		shotTime += Time::deltaTime();

		// 15秒たったら別のステートに変更する
		if (actionTime >= BossAttackTime::shotAttack) {
			auto rand = static_cast<BossPattern>(Randam::getRandomRange(0, 8));
			_boss->changeState(rand);
		}

		if (shotTime >= BossAttackTime::shotInterval) {
			shotTime = 0.0f;

			auto direction = Vector2{ (_boss->getDir() == Direction::Right) ? 7.0f : -7.0f, 0.0f };
			auto pos = _boss->transform.pos;
			pos.y += 16.0f;
			BulletPtr bullet{ new Bullet{ pos, direction } };
			bullet->onStart();
			bullet->setAttack(_boss->getParameter().attack);
			BulletManager::getIns()->addBullet(bullet);
		}
	}
}