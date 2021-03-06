#ifndef STAGEEVENT_H
#define STAGEEVENT_H

#include "Lib.h"
#include "EventObject.h"

namespace gnGame {

	class StageEvent : public EventObject
	{
	public:
		StageEvent(const Vector2& _pos, GameScene* _gameScene);
		~StageEvent() = default;

		void onUpdate() override;
		void onEvent() override;

		ICollider& getCollider() override;

	private:
		BoxCollider collider;  // イベントオブジェクトの当たり判定
	};
}


#endif // !STAGEEVENT_H
