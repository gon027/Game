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
	{
		waitAnimSprite.setTexture(TextureManager::getTexture("Enemy4_Wait"));
	}

	ShotEnemy::ShotEnemy(GameScene* _gameScene, const Vector2& _pos, const ActorParameter _parameter, Direction _direction)
		: Enemy(_pos, _parameter)
		, gameScene(_gameScene)
		, enemyAttack(this)
		, waitAnimSprite(7, 1, 12.0f)
	{
		this->direction = _direction;
		this->isFlip = (_direction == Direction::Left) ? false : true;
		waitAnimSprite.setTexture(TextureManager::getTexture("Enemy4_Wait"));
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
		this->physics();
		this->transform.pos = intersectTileMap();
		enemyAttack.execute();

		auto screen(Camera::toScreenPos(this->transform.pos));
		collider.update(screen, 32.0f, 32.0f);
		waitAnimSprite.draw(screen, transform.scale, transform.angle, true, isFlip);
	}
}


