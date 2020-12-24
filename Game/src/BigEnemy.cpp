#include "../include/BigEnemy.h"
#include "../include/Camera.h"
#include "../include/TextureManager.h"

namespace gnGame {

	BigEnemy::BigEnemy()
		: Enemy()
	{
	}

	BigEnemy::BigEnemy(const Vector2& _pos, const ActorParameter _parameter)
		: Enemy(_pos, _parameter)
	{
	}

	void BigEnemy::onStart()
	{
		
		this->sprite.setTexture(TextureManager::getTexture("Tako"));

		bounds.minPos.setPos(0, 0);
		bounds.maxPos.setPos(48, 48);
		bounds.size.setPos(bounds.maxPos - bounds.minPos);
		bounds.center.setPos(bounds.size.half());
	}

	void BigEnemy::onUpdate()
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
