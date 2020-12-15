#include "../include/GoalEvent.h"
#include "../include/Camera.h"
#include "../include/GameScene.h"
#include "../include/StageManager.h"

namespace gnGame {

	GoalEvent::GoalEvent(const Vector2& _pos, GameScene* _gameScene)
		: EventObject(_pos, _gameScene)
		, size(32, 32)
	{
	}

	void GoalEvent::onStart()
	{

	}

	void GoalEvent::onUpdate()
	{
		auto screen = Camera::toScreenPos(this->transform.pos);

		this->collider.update(screen, size.getWidth(), size.getHeight());

		r.setColor(Color{ 255, 128, 0 });
		r.setPos({ screen.x - size.getWidth() / 2.0f, screen.y - size.getHeight() / 2.0f });
		r.setSize(size.getWidth());
		r.draw();
	}

	void GoalEvent::onEvent()
	{
		StageManager::getIns()->unlockStage();
		gameScene->changeSelectScene();
	}

	void GoalEvent::setCollisionSize(int _width, int _height)
	{
		size.setSize(_width, _height);
	}

}
