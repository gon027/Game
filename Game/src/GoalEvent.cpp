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

	void GoalEvent::onUpdate()
	{
		auto screen = Camera::toScreenPos(this->transform.pos);
		this->collider.update(
			screen,
			static_cast<float>(size.getWidth()),
			static_cast<float>(size.getHeight())
		);
	}

	void GoalEvent::onEvent()
	{
		auto unlockStage = StageManager::getIns()->getUnlockCurrentStage();
		auto currentStage = StageManager::getIns()->getCurrentStage();

		// ���݂̃X�e�[�W�ԍ��ƃA�����b�N����Ă���X�e�[�W�̔ԍ����������A���̃X�e�[�W���J������
		if (currentStage == unlockStage) {
			StageManager::getIns()->unlockStage();
		}

		gameScene->changeSelectScene();
	}

	void GoalEvent::setCollisionSize(int _width, int _height)
	{
		size.setSize(_width, _height);
	}

	ICollider& GoalEvent::getCollider()
	{
		return collider;
	}

}
