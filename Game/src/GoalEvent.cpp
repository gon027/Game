#include "../include/GoalEvent.h"
#include "../include/Camera.h"
#include "../include/GameScene.h"
#include "../include/StageManager.h"
#include "../include/TextureManager.h"

namespace gnGame {

	GoalEvent::GoalEvent(const Vector2& _pos, GameScene* _gameScene)
		: EventObject(_pos, _gameScene)
		, sprite()
	{
		sprite.setTexture(TextureManager::getTexture("Goal"));
	}

	void GoalEvent::onUpdate()
	{
		auto screen = Camera::toScreenPos(this->transform.pos);

		Rect r;
		r.setSize(96.0f, 96.0f);
		r.setColor(Color::Blue);
		r.setPos(screen);
		r.draw();

		screen += {48.0f, 32.0f};
		this->collider.update(screen, 96.0f, 96.0f);

		screen += {0.0f, 16.0f};
		sprite.draw(screen, Vector2::One, 0.0f);
	}

	void GoalEvent::onEvent()
	{
		auto unlockStage = StageManager::getIns()->getUnlockCurrentStage();
		auto currentStage = StageManager::getIns()->getCurrentStage();

		// 現在のステージ番号とアンロックされているステージの番号が同じ時、次のステージを開放する
		if (currentStage == unlockStage) {
			StageManager::getIns()->unlockStage();
		}

		gameScene->changeSelectScene();
	}

	ICollider& GoalEvent::getCollider()
	{
		return collider;
	}

}
