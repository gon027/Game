#include "../include/WalkEnemy.h"
#include "../include/Camera.h"
#include "../include/TextureManager.h"

namespace gnGame {

	WalkEnemy::WalkEnemy()
		: Enemy()
		, waitAnimSprite(7, 1, 7.0f)
		, actionAnimSprite(7, 1, 12.0f)
	{
	}

	WalkEnemy::WalkEnemy(const Vector2 _pos, const ActorParameter _parameter)
		: Enemy(_pos, _parameter)
		, waitAnimSprite(7, 1, 7.0f)
		, actionAnimSprite(7, 1, 12.0f)
	{
	}

	void WalkEnemy::onStart()
	{
		waitAnimSprite.setTexture(TextureManager::getTexture("Enemy1_Wait"));
		actionAnimSprite.setTexture(TextureManager::getTexture("Enemy1_Action"));

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

		action();
	}

	void WalkEnemy::action()
	{
		frameTimer.update();

		if (actionState == EnemyActionState::Wait) {
			auto screen(Camera::toScreenPos(this->transform.pos));
			collider.update(screen, 32.0f, 32.0f);
			waitAnimSprite.draw(screen, transform.scale, transform.angle, true, isFlip);

			if (frameTimer.isTimeUp(3.0f)) {
				actionState = EnemyActionState::Action;
				this->velocity = Vector2::Zero;
				frameTimer.reset();
			}
		}
		else {
			this->moveEnemy();
			this->transform.pos = intersectTileMap();

			auto screen(Camera::toScreenPos(this->transform.pos));
			collider.update(screen, 32.0f, 32.0f);
			actionAnimSprite.draw(screen, transform.scale, transform.angle, true, isFlip);

			if (frameTimer.isTimeUp(7.5f)) {
				actionState = EnemyActionState::Wait;
				frameTimer.reset();
			}
		}
	}
}
