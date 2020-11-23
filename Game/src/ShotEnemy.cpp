#include "../include/ShotEnemy.h"
#include "../include/Camera.h"
#include "../include/Bullet.h"
#include "../include/TextureManager.h"
#include "../include/BulletManager.h"

namespace gnGame {

	namespace {
		constexpr float SHOTINTERVAL = 1.0f;
	}


	ShotEnemy::ShotEnemy()
		: Enemy()
		, shotTime(0)
	{
	}

	ShotEnemy::ShotEnemy(const Vector2& _pos)
		: Enemy(_pos)
		, shotTime(0)
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

		shot();

		this->transform.pos = intersectTileMap();

		if (!this->isOnScreen()) {
			return;
		}

		auto screen(Camera::toScreenPos(this->transform.pos));
		collider.update(screen, 32.0f, 32.0f);
		sprite.draw(screen, transform.scale, transform.angle, true, isFlip);

	}

	void ShotEnemy::shot()
	{
		shotTime += Time::deltaTime();

		// 1•b‚É1‰ñ‘Å‚Â
		if (shotTime >= SHOTINTERVAL) {
			if (dir == Direction::Left) {
				BulletPtr bulletPtr(new Bullet(this->transform.pos, Vector2{ -10.0f, 0.0f }));
				bulletPtr->onStart();
				BulletManager::getIns()->addBullet(bulletPtr);
			}
			else if (dir == Direction::Right) {
				BulletPtr bulletPtr(new Bullet(this->transform.pos, Vector2{ 10.0f, 0.0f }));
				bulletPtr->onStart();
				BulletManager::getIns()->addBullet(bulletPtr);
			}
			shotTime = 0;
		}
	}
}
