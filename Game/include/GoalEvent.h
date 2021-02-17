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

		ICollider& getCollider() override;

	private:
		BoxCollider collider;  // イベントオブジェクトの当たり判定
		Sprite sprite;
	};

}


#endif // !GOALEVENT_H
