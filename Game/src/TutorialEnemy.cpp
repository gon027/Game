#include "../include/TutorialEnemy.h"
#include "../include/Camera.h"
#include "../include/TextureManager.h"

namespace gnGame {

	TutorialEnemy::TutorialEnemy(const Vector2 _pos)
		: Enemy(_pos, { 20.0f, 0.0f, 0.0f, 0.0f, 0.0f })
		, waitAnim(9, 1, 12.0f)
	{
		waitAnim.setTexture(TextureManager::getTexture("Tutorial_Boss"));
	}

	void TutorialEnemy::onStart()
	{
		bounds.minPos.setPos(0, 0);
		bounds.maxPos.setPos(64, 64);
		bounds.size.setPos(bounds.maxPos - bounds.minPos);
		bounds.center.setPos(bounds.size.half());
	}

	void TutorialEnemy::onUpdate()
	{
		if (!this->isActive) {
			return;
		}

		this->physics();
		this->transform.pos = intersectTileMap();
		auto screen = Camera::toScreenPos(this->transform.pos);
		collider.update(screen, 64.0f, 64.0f);
		waitAnim.draw(screen, Vector2::One, 0.0f);
	}
}