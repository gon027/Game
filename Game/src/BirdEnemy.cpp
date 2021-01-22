#include "../include/BirdEnemy.h"
#include "../include/Camera.h"
#include "../include/TextureManager.h"

namespace gnGame {

	BirdEnemy::BirdEnemy()
		: Enemy()
	{
	}

	BirdEnemy::BirdEnemy(const Vector2& _pos, const ActorParameter _parameter)
		: Enemy(_pos, _parameter)
	{
	}

	void BirdEnemy::onStart()
	{
		this->sprite.setTexture(TextureManager::getTexture("Tako"));

		bounds.minPos.setPos(0, 0);
		bounds.maxPos.setPos(32, 32);
		bounds.size.setPos(bounds.maxPos - bounds.minPos);
		bounds.center.setPos(bounds.size.half());
	}

	void BirdEnemy::onUpdate()
	{
		if (!this->isActive) {
			return;
		}

		if (!Camera::isOnScreen(this->transform.pos)) {
			return;
		}

		this->moveEnemy();
		this->transform.pos = intersectTileMap();

		auto screen(Camera::toScreenPos(this->transform.pos));
		collider.update(screen, 48.0f, 48.0f);
		sprite.draw(screen, transform.scale, transform.angle, true, isFlip);
	}
}