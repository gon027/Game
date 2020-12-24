#include "../include/StageEvent.h"
#include "../include/GameScene.h"
#include "../include/Camera.h"

namespace gnGame {

	StageEvent::StageEvent(const Vector2& _pos, GameScene* _gameScene)
		: EventObject(_pos, _gameScene)
		, r()
	{
	}

	void StageEvent::onUpdate()
	{
		auto screen = Camera::toScreenPos(this->transform.pos);
		this->collider.update(screen, 32.0f, 32.0f);

		/*
		r.setColor(Color{ 255, 128, 0 });
		r.setPos({ screen.x - 16, screen.y - 16 });
		r.setSize(32.f);
		r.draw();
		*/
	}

	void StageEvent::onEvent()
	{
		gameScene->nextMap();
	}

}
