#include "../include/BossState.h"
#include "../include/Lib.h"
#include "../include/Boss.h"
#include "../include/Bullet.h"
#include "../include/BulletManager.h"
#include "../include/Randam.h"
#include "../include/GameScene.h"

namespace gnGame {

	// ---------- BossWait ----------
	BossAction::BossWait::BossWait()
		: waitTime(0.0f)
	{
	}

	void BossAction::BossWait::update(Boss* _boss)
	{
		waitTime += Time::deltaTime();

		if (waitTime >= MaxWaitTime) {
			auto rand = static_cast<BossPattern>(Randama::getRandomRange(0, 5));
			_boss->changeState(rand);
		}
	}

	// ---------- BossMove1 ----------
	const Vector2 BossAction::BossMove1::TargetPoint{ 800, 600 };

	BossAction::BossMove1::BossMove1()
		: moveTime(0.0f)
	{
	}

	void BossAction::BossMove1::update(Boss* _boss)
	{
		if (moveTime >= MaxMoveTime) {
			auto rand = static_cast<BossPattern>(Randama::getRandomRange(0, 5));
			_boss->changeState(rand);
		}

		const auto start = _boss->transform.pos;
		const auto end = TargetPoint;

		float rate = moveTime / MaxMoveTime;
		float nextX = start.x + (end.x - start.x) * rate;
		float nextY = start.y + (end.y - start.y) * rate;
		//Debug::drawFormatText(100, 100, Color::Black, "%lf", moveTime);
		//Debug::drawFormatText(100, 120, Color::Black, "%lf", rate);
		_boss->transform.pos.setPos(nextX, nextY);
		
		moveTime += Time::deltaTime();
	}

	// ---------- BossMove2 ----------
	const Vector2 BossAction::BossMove2::TargetPoint{ 100, 600 };

	BossAction::BossMove2::BossMove2()
		: moveTime(0.0f)
	{
	}

	void BossAction::BossMove2::update(Boss* _boss)
	{
		if (moveTime >= MaxMoveTime) {
			auto rand = static_cast<BossPattern>(Randama::getRandomRange(0, 5));
			_boss->changeState(BossPattern::Move1);
		}

		const auto start = _boss->transform.pos;
		const auto end = TargetPoint;

		float rate = moveTime / MaxMoveTime;
		float nextX = start.x + (end.x - start.x) * rate;
		float nextY = start.y + (end.y - start.y) * rate;
		_boss->transform.pos.setPos(nextX, nextY);

		moveTime += Time::deltaTime();
	}

	// ---------- BossAction1 ----------
	BossAction::BossAction1::BossAction1(const GameScene* _gameScene)
		: gameScene(_gameScene)
		, actionTime(0.0f)
		, shotTime(0.0f)
	{
	}

	void BossAction::BossAction1::update(Boss* _boss)
	{
		actionTime += Time::deltaTime();
		shotTime += Time::deltaTime();

		if (actionTime >= 15.0f) {
			//_boss->changeState(BossPattern::Wait);
			auto rand = static_cast<BossPattern>(Randama::getRandomRange(0, 5));
			_boss->changeState(rand);
		}

		if (shotTime >= 1.0f) {
			float accel = 5.0f;

			auto playerPos = gameScene->getPlayer()->transform.pos - _boss->transform.pos;
			float angle = atan2f(playerPos.y, playerPos.x);

			auto dir = Vector2{ cosf(angle) * accel, sinf(angle) * accel };
			BulletPtr bullet{ new Bullet{_boss->transform.pos, dir} };
			bullet->onStart();
			bullet->setAttack(10.0f);
			BulletManager::getIns()->addBullet(bullet);
			accel += 0.2f;

			shotTime = 0.0f;
		}
	}

	// ---------- BossAction2 ----------
	BossAction::BossAction2::BossAction2(const GameScene* _gameScene)
		: gameScene(_gameScene)
		, actionTime(0.0f)
		, shotTime(0.0f)
	{
	}

	void BossAction::BossAction2::update(Boss* _boss)
	{
		actionTime += Time::deltaTime();
		shotTime += Time::deltaTime();

		if (actionTime >= 10.0f) {
			//_boss->changeState(BossPattern::Wait);
			auto rand = static_cast<BossPattern>(Randama::getRandomRange(0, 5));
			_boss->changeState(rand);
		}
		
		if (shotTime >= 1.0f) {
			float accel = 1.0f;

			auto pos = gameScene->getPlayer()->transform.pos - _boss->transform.pos;
			float angle = atan2f(pos.y, pos.x);

			const float r = toRadians(Range);
			const float startAngle = angle - r;
			const float endAngle = angle + r;
			const float inc{ (r * 2) / 5.0f };
			
			// [angle - theta, angle + theta]‚Ì”ÍˆÍ•ª’e‚ð”­ŽË‚·‚é
			for (float rad{ startAngle }; rad < endAngle; rad += inc) {
				auto dir = Vector2{ cosf(rad) * 5.0f, sinf(rad) * 5.0f };
				BulletPtr bullet{ new Bullet{_boss->transform.pos, dir} };
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

		// 15•b‚½‚Á‚½‚ç•Ê‚ÌƒXƒe[ƒg‚É•ÏX‚·‚é
		if (actionTime >= 15.0f) {
			//_boss->changeState(BossPattern::Wait);
			auto rand = static_cast<BossPattern>(Randama::getRandomRange(0, 5));
			_boss->changeState(rand);
		}

		// 2•b‚É1‰ñ”­ŽË‚·‚é
		if (shotTime >= 2.0f) {
			shotTime = 0.0f;

			const float inc{ tau / 10.0f };
			float accel = 1.0f;
			for (int num{ 0 }; num < 3; ++num) {

				float angle{ (num % 2 == 0) ? 0.0f : -inc / 2.0f };
				float end{ (num % 2 == 0) ? tau : tau - inc / 2.0f };

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