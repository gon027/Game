#include "../include/StageEvent.h"
#include "../include/GameScene.h"
#include "../include/Camera.h"

namespace gnGame {

	StageEvent::StageEvent(const Vector2& _pos, GameScene* _gameScene)
		: EventObject(_pos, _gameScene)
	{
	}

	void StageEvent::onUpdate()
	{
		auto screen = Camera::toScreenPos(this->transform.pos);

		Rect r;
		r.setSize(32, 128);
		r.setColor(Color::Blue);
		r.setPos(screen);
		r.draw();

		screen += {16.0f, 32.0f};
		this->collider.update(screen, 32.0f, 128.0f);
		
	}

	void StageEvent::onEvent()
	{
		gameScene->nextMap();
	}

	ICollider& StageEvent::getCollider()
	{
		return collider;
	}

}