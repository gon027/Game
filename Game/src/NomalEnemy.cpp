#include "../include/NomalEnemy.h"
#include "../include/Camera.h"
#include "../include/TextureManager.h"

namespace gnGame {

	NomalEnemy::NomalEnemy()
		: Enemy()
		, waitAnimSprite(7, 1, 12.0f)
		, actionAnimSprite(7, 1, 12.0f) 
	{
	}

	NomalEnemy::NomalEnemy(const Vector2& _pos, const ActorParameter _parameter)
		: Enemy(_pos, _parameter)
		, waitAnimSprite(7, 1, 12.0f)
		, actionAnimSprite(7, 1, 12.0f)
	{
	}

	void NomalEnemy::onStart()
	{
		waitAnimSprite.setTexture(TextureManager::getTexture("Enemy2_Wait"));
		actionAnimSprite.setTexture(TextureManager::getTexture("Enemy2_Action"));

		bounds.minPos.setPos(0, 0);
		bounds.maxPos.setPos(32, 32);
		bounds.size.setPos(bounds.maxPos - bounds.minPos);
		bounds.center.setPos(bounds.size.half());
	}

	void NomalEnemy::onUpdate()
	{
		if (!this->isActive) {
			return;
		}

		if (!Camera::isOnScreen(this->transform.pos)) {
			return;
		}

		action();
	}

	void NomalEnemy::action()
	{
		frameTime.update();

		if (actionState == EnemyActionState::Wait) {
			this->physics();
			this->transform.pos = intersectTileMap();

			auto screen(Camera::toScreenPos(this->transform.pos));
			collider.update(screen, 32.0f, 32.0f);
			waitAnimSprite.draw(screen, transform.scale, transform.angle, true, isFlip);

			if (frameTime.isTimeUp(5.0f)) {
				actionState = EnemyActionState::Action;
				this->velocity = Vector2::Zero;
				frameTime.reset();
			}
		}
		else {
			this->moveEnemy();
			this->transform.pos = intersectTileMap();

			auto screen(Camera::toScreenPos(this->transform.pos));
			collider.update(screen, 32.0f, 32.0f);
			actionAnimSprite.draw(screen, transform.scale, transform.angle, true, isFlip);

			if (frameTime.isTimeUp(1.0f)) {
				actionState = EnemyActionState::Wait;
				frameTime.reset();
			}
		}
	}

}