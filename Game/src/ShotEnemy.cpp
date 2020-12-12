#include "../include/ShotEnemy.h"
#include "../include/Camera.h"
#include "../include/Bullet.h"
#include "../include/TextureManager.h"
#include "../include/BulletManager.h"

namespace gnGame {

	ShotEnemy::ShotEnemy()
		: Enemy()
		, enemyAttack(this)
	{
	}

	ShotEnemy::ShotEnemy(const Vector2& _pos)
		: Enemy(_pos)
		, enemyAttack(this)
	{
	}

	void ShotEnemy::onStart()
	{
		this->sprite.setTexture(TextureManager::getTexture("Enemy1"));
	
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
		enemyAttack.execute();

		this->transform.pos = intersectTileMap();

		if (!this->isOnScreen()) {
			return;
		}

		auto screen(Camera::toScreenPos(this->transform.pos));
		collider.update(screen, 32.0f, 32.0f);
		sprite.draw(screen, transform.scale, transform.angle, true, isFlip);
	}
}
