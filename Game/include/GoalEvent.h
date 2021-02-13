#ifndef GOALEVENT_H
#define GOALEVENT_H

#include "EventObject.h"

namespace gnGame {

	class GameScene;

	class GoalEvent : public EventObject
	{
	public:
		GoalEvent(const Vector2& _pos, GameScene* _gameScene);
		~GoalEvent() = default;

		void onUpdate() override;
		void onEvent() override;

		void setCollisionSize(int _width, int _height);

		ICollider& getCollider() override;

	private:
		BoxCollider collider;  // �C�x���g�I�u�W�F�N�g�̓����蔻��
		Size size;
	};

}


#endif // !GOALEVENT_H
