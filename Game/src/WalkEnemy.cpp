#include "../include/WalkEnemy.h"
#include "../include/Camera.h"
#include "../include/TextureManager.h"

namespace gnGame {

	WalkEnemy::WalkEnemy()
		: Enemy()
	{
	}

	WalkEnemy::WalkEnemy(const Vector2 _pos)
		: Enemy(_pos)
	{
	}

	void WalkEnemy::onStart()
	{
		this->sprite.setTexture(TextureManager::getTexture("Enemy1"));

		bounds.minPos.setPos(0, 0);
		bounds.maxPos.setPos(32, 32);
		bounds.size.setPos(bounds.maxPos - bounds.minPos);
		bounds.center.setPos(bounds.size.half());
	}

	void WalkEnemy::onUpdate()
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
		collider.update(screen, 32.0f, 32.0f);
		sprite.draw(screen, transform.scale, transform.angle, true, isFlip);
	}

}
