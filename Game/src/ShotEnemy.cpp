#include "../include/ShotEnemy.h"
#include "../include/Camera.h"
#include "../include/Bullet.h"
#include "../include/TextureManager.h"
#include "../include/BulletManager.h"
#include "../include/GameScene.h"

namespace gnGame {

	EnemyState::BulletShotPattern1::BulletShotPattern1(Enemy* _enemyPtr)
		: EnemyAttack(_enemyPtr)
		, frameTimer()
	{
	}

	void EnemyState::BulletShotPattern1::execute()
	{
		frameTimer.update();

		// ‘S•ûˆÊ‚É’e‚ð”­ŽË‚·‚é

		const auto angle = tau / 10.0f;
		if (frameTimer.isTimeUp(InterVal)) {
			frameTimer.reset();

			auto accel{ 1.0f };
			for (int _ = 0; _ < 5; ++_) {
				float rad = 0.0f;
				for (auto i{ 0.0f }; i < 10; ++i) {
					rad += angle;
					auto x{ cosf(rad) * accel };
					auto y{ sinf(rad) * accel };
					BulletPtr bulletPtr(new Bullet(enemyPtr->transform.pos, Vector2{ x, y }));
					bulletPtr->onStart();
					bulletPtr->setAttack(enemyPtr->getParameter().attack);
					BulletManager::getIns()->addBullet(bulletPtr);
				}
				accel += 0.2f;
			}
		}
	}

	ShotEnemy::ShotEnemy()
		: Enemy()
		, gameScene(nullptr)
		, enemyAttack(this)
		//, bShotPattern1(this)
		, waitAnimSprite(7, 1, 12.0f)
		, actionAnimSprite(7, 1, 12.0f)
		, frameTime()
	{
	}

	ShotEnemy::ShotEnemy(GameScene* _gameScene, const Vector2& _pos, const ActorParameter _parameter)
		: Enemy(_pos, _parameter)
		, gameScene(_gameScene)
		, enemyAttack(this)
		//, bShotPattern1(this)
		, waitAnimSprite(7, 1, 12.0f)
		, actionAnimSprite(7, 1, 12.0f)
		, frameTime()
	{
	}

	void ShotEnemy::onStart()
	{
		waitAnimSprite.setTexture(TextureManager::getTexture("Enemy4_Wait"));
		actionAnimSprite.setTexture(TextureManager::getTexture("Enemy4_Action"));

		bounds.minPos.setPos(0, 0);
		bounds.maxPos.setPos(32, 32);
		bounds.size.setPos(bounds.maxPos - bounds.minPos);
		bounds.center.setPos(bounds.size.half());
	}

	void ShotEnemy::onUpdate()
	{
		if (!this->isActive) {
			return;
		}
		
		if (!Camera::isOnScreen(this->transform.pos)) {
			return;
		}

		action();
	}

	void ShotEnemy::action()
	{
		frameTime.update();

		if (actionState == EnemyActionState::Action) {
			moveEnemy();
			enemyAttack.execute(gameScene->getPlayer());

			this->transform.pos = intersectTileMap();

			auto screen(Camera::toScreenPos(this->transform.pos));
			collider.update(screen, 32.0f, 32.0f);
			actionAnimSprite.draw(screen, transform.scale, transform.angle, true, isFlip);

			if (frameTime.isTimeUp(5.0f)) {
				actionState = EnemyActionState::Wait;
				this->velocity = Vector2::Zero;
				frameTime.reset();
			}
		}
		else {

			auto screen(Camera::toScreenPos(this->transform.pos));

			collider.update(screen, 32.0f, 32.0f);
			waitAnimSprite.draw(screen, transform.scale, transform.angle, true, isFlip);

			if (frameTime.isTimeUp(5.0f)) {
				actionState = EnemyActionState::Action;
				frameTime.reset();
			}
		}
	}
}


