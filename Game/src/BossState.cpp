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
			auto rand = static_cast<BossPattern>(Randam::getRandomRange(3, 5));
			_boss->changeState(rand);
		}
	}

	// ---------- BossMove1 ----------
	BossAction::BossMove1::BossMove1()
	{
		MoveParams::moveTime = 0.0f;
		MoveParams::moveRate = 0.0f;
	}

	void BossAction::BossMove1::update(Boss* _boss)
	{
		// 最初呼び出したとき
		if (MoveParams::moveTime == 0) {
			_boss->setDirection(Direction::Left);
			MoveParams::start = _boss->transform.pos;
		}

		if (MoveParams::moveTime >= MoveParams::MaxMoveTime) {
			_boss->setDirection(Direction::Right);
			_boss->changeState(BossPattern::Wait, 1.0f);
		}

		MoveParams::moveRate = MoveParams::moveTime / MoveParams::MaxMoveTime;
		_boss->transform.pos.setPos(
			MoveParams::leap(MoveParams::start, MoveParams::TargetPoint1, MoveParams::moveRate)
		);

		MoveParams::moveTime += Time::deltaTime();
	}

	// ---------- BossMove2 ----------
	BossAction::BossMove2::BossMove2()
	{
		MoveParams::moveTime = 0.0f;
		MoveParams::moveRate = 0.0f;
	}

	void BossAction::BossMove2::update(Boss* _boss)
	{
		if (MoveParams::moveTime == 0) {
			_boss->setDirection(Direction::Right);
			MoveParams::start = _boss->transform.pos;
		}

		if (MoveParams::moveTime >= MoveParams::MaxMoveTime) {
			_boss->setDirection(Direction::Left);
			_boss->changeState(BossPattern::Wait, 1.0f);
		}

		MoveParams::moveRate = MoveParams::moveTime / MoveParams::MaxMoveTime;
		_boss->transform.pos.setPos(
			MoveParams::leap(MoveParams::start, MoveParams::TargetPoint2, MoveParams::moveRate)
		);

		MoveParams::moveTime += Time::deltaTime();
	}

	// ---------- BossAction1 ----------
	BossAction::BossAction1::BossAction1(GameScene* _gameScene)
		: gameScene(_gameScene)
		, actionTime(0.0f)
		, shotTime(0.0f)
	{
	}

	void BossAction::BossAction1::update(Boss* _boss)
	{
		actionTime += Time::deltaTime();
		shotTime += Time::deltaTime();

		if (actionTime >= 1.0f) {
			auto rand = static_cast<BossPattern>(Randam::getRandomRange(0, 5));
			_boss->changeState(rand);
		}

		if (shotTime >= 1.0f) {
			float accel = 5.0f;

			auto playerPos = gameScene->getPlayer()->transform.pos - _boss->transform.pos;
			float angle = atan2f(playerPos.y, playerPos.x);

			auto direction = Vector2{ cosf(angle) * accel, sinf(angle) * accel };
			BulletPtr bullet{ new Bullet{_boss->transform.pos, direction} };
			bullet->onStart();
			bullet->setAttack(10.0f);
			BulletManager::getIns()->addBullet(bullet);
			accel += 0.2f;

			shotTime = 0.0f;
		}
	}

	// ---------- BossAction2 ----------
	BossAction::BossAction2::BossAction2(GameScene* _gameScene)
		: gameScene(_gameScene)
		, actionTime(0.0f)
		, shotTime(0.0f)
	{
	}

	void BossAction::BossAction2::update(Boss* _boss)
	{
		actionTime += Time::deltaTime();
		shotTime += Time::deltaTime();

		if (actionTime >= 1.0f) {
			auto rand = static_cast<BossPattern>(Randam::getRandomRange(0, 5));
			_boss->changeState(rand);
		}
		
		if (shotTime >= 15.0f) {
			float accel = 1.0f;

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
				bullet->setAttack(10.0f);
				BulletManager::getIns()->addBullet(bullet);
			}
						
			shotTime = 0.0f;
		}
	}

	// --------- BossAction3 ----------
	BossAction::BossAction3::BossAction3()
		: actionTime(0.0f)
		, shotTime(0.0f)
	{
	}

	void BossAction::BossAction3::update(Boss* _boss)
	{
		actionTime += Time::deltaTime();
		shotTime += Time::deltaTime();

		// 15秒たったら別のステートに変更する
		if (actionTime >= 1.0f) {
			auto rand = static_cast<BossPattern>(Randam::getRandomRange(0, 5));
			_boss->changeState(rand);
		}

		// 2秒に1回発射する
		if (shotTime >= 2.0f) {
			shotTime = 0.0f;

			const float inc{ tau / 12.0f };
			float accel = 1.0f;
			for (int num{ 0 }; num < 3; ++num) {

				float angle{ 0.0f - inc / 1.75f };
				float end{ tau - inc / 1.75f };

				for (; angle < end; angle += inc) {
					auto x{ cosf(angle) * accel };
					auto y{ sinf(angle) * accel };
					BulletPtr bullet{ new Bullet{_boss->transform.pos, {x, y}} };
					bullet->onStart();
					bullet->setAttack(_boss->getParameter().attack);
					BulletManager::getIns()->addBullet(bullet);
				}
				accel += 0.2f;
			}
		}
	}
}