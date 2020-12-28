#include "BossState.h"
#include "include/Lib.h"
#include "include/Boss.h"
#include "include/Bullet.h"
#include "include/BulletManager.h"

namespace gnGame {

	BossAction::BossWait::BossWait()
		: waitTime(0.0f)
	{
	}

	void BossAction::BossWait::update(Boss* _boss)
	{
		waitTime += Time::deltaTime();

		if (waitTime >= MaxWaitTime) {
			_boss->changeState(BossPattern::Attack2);
		}

		_boss->transform.pos.x += 2.0f;
	}

	Vector2 BossAction::BossMove1::TargetPoint{ 800, 500 };

	BossAction::BossMove1::BossMove1()
		: moveTime(0.0f)
	{
	}

	void BossAction::BossMove1::update(Boss* _boss)
	{
		_boss->transform.pos.x += 2.0f;

		if (_boss->transform.pos.x >= TargetPoint.x) {
			_boss->changeState(BossPattern::Move2);
		}
	}

	Vector2 BossAction::BossMove2::TargetPoint{ 100, 500 };

	BossAction::BossMove2::BossMove2()
		: moveTime(0.0f)
	{
	}

	void BossAction::BossMove2::update(Boss* _boss)
	{
		_boss->transform.pos.x -= 2.0f;

		if (_boss->transform.pos.x <= TargetPoint.x) {
			_boss->changeState(BossPattern::Move1);
		}
	}

	BossAction::BossAction1::BossAction1()
		: actionTime(0.0f)
		, shotTime(0.0f)
	{
	}

	void BossAction::BossAction1::update(Boss* _boss)
	{
		actionTime += Time::deltaTime();
		shotTime += Time::deltaTime();

		if (actionTime >= 15.0f) {
			_boss->changeState(BossPattern::Wait);
		}

		if (shotTime >= 1.0f) {
			float accel = 1.0f;
			for (int i{ 0 }; i < 5; ++i) {
				auto dir = Vector2{ 7.0f + accel * static_cast<float>(i), 0.0f };
				BulletPtr bullet{ new Bullet{_boss->transform.pos, dir} };
				bullet->onStart();
				bullet->setAttack(10.0f);
				BulletManager::getIns()->addBullet(bullet);
				accel += 0.2f;
			}
			shotTime = 0.0f;
		}
	}

	BossAction::BossAction2::BossAction2()
		: actionTime(0.0f)
		, shotTime(0.0f)
	{
	}

	void BossAction::BossAction2::update(Boss* _boss)
	{
		actionTime += Time::deltaTime();
		shotTime += Time::deltaTime();

		if (actionTime >= 15.0f) {
			_boss->changeState(BossPattern::Wait);
		}

		if (shotTime >= 1.0f) {
			float accel = 1.0f;
			for (int i{ 0 }; i < 5; ++i) {
				auto dir = Vector2{ -7.0f + accel * static_cast<float>(i), 0.0f };
				BulletPtr bullet{ new Bullet{_boss->transform.pos, dir} };
				bullet->onStart();
				bullet->setAttack(10.0f);
				BulletManager::getIns()->addBullet(bullet);
				accel += 0.2f;
			}
			shotTime = 0.0f;
		}
	}

	BossAction::BossAction3::BossAction3()
		: actionTime(0.0f)
		, shotTime(0.0f)
	{
	}

	void BossAction::BossAction3::update(Boss* _boss)
	{
	}
}