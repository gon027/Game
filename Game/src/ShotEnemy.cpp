#include "../include/ShotEnemy.h"
#include "../include/Camera.h"
#include "../include/Bullet.h"
#include "../include/TextureManager.h"
#include "../include/BulletManager.h"
#include "../include/GameScene.h"

namespace gnGame {

	ShotEnemy::ShotEnemy()
		: Enemy()
		, gameScene(nullptr)
		, enemyAttack(this)
		, waitAnimSprite(7, 1, 12.0f)
		, actionAnimSprite(7, 1, 12.0f)
		, frameTime()
	{
		waitAnimSprite.setTexture(TextureManager::getTexture("Enemy4_Wait"));
		actionAnimSprite.setTexture(TextureManager::getTexture("Enemy4_Action"));
	}

	ShotEnemy::ShotEnemy(GameScene* _gameScene, const Vector2& _pos, const ActorParameter _parameter)
		: Enemy(_pos, _parameter)
		, gameScene(_gameScene)
		, enemyAttack(this)
		, waitAnimSprite(7, 1, 12.0f)
		, actionAnimSprite(7, 1, 12.0f)
		, frameTime()
	{
		waitAnimSprite.setTexture(TextureManager::getTexture("Enemy4_Wait"));
		actionAnimSprite.setTexture(TextureManager::getTexture("Enemy4_Action"));
	}

	void ShotEnemy::onStart()
	{
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

		if (actionState == EnemyActionState::Wait) {
			this->physics();
			this->transform.pos = intersectTileMap();

			auto screen(Camera::toScreenPos(this->transform.pos));
			collider.update(screen, 32.0f, 32.0f);
			waitAnimSprite.draw(screen, transform.scale, transform.angle, true, isFlip);

			if (frameTime.isTimeUp(3.0f)) {
				actionState = EnemyActionState::Action;
				frameTime.reset();
			}
		}
		else {
			this->moveEnemy();
			this->physics();
			enemyAttack.execute(gameScene->getPlayer());
			this->transform.pos = intersectTileMap();

			auto screen(Camera::toScreenPos(this->transform.pos));
			collider.update(screen, 32.0f, 32.0f);
			actionAnimSprite.draw(screen, transform.scale, transform.angle, true, isFlip);

			if (frameTime.isTimeUp(7.5f)) {
				actionState = EnemyActionState::Wait;
				this->velocity = Vector2::Zero;
				frameTime.reset();
			}
		}
	}
}


