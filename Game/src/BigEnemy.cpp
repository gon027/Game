#include "../include/BigEnemy.h"
#include "../include/Camera.h"
#include "../include/TextureManager.h"

namespace gnGame {

	BigEnemy::BigEnemy(const Vector2& _pos, const ActorParameter _parameter)
		: Enemy(_pos, _parameter)
		, frameTime()
		, waitAnimSprite(9, 1, 12.0f)
		, actionAnimSprite(7, 1, 12.0f)
	{
		waitAnimSprite.setTexture(TextureManager::getTexture("BigEnemy_Wait"));
		actionAnimSprite.setTexture(TextureManager::getTexture("BigEnemy_Action"));
	}

	void BigEnemy::onStart()
	{
		bounds.minPos.setPos(0, 0);
		bounds.maxPos.setPos(64, 64);
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

		action();
	}

	void BigEnemy::action()
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
