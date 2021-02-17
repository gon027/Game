#ifndef TRAPEVENT_H
#define TRAPEVENT_H

#include <vector>
#include "Lib.h"
#include "EventObject.h"

namespace gnGame {
	class TrapEvent : public EventObject {
	public:
		TrapEvent(const Vector2& _pos, GameScene* _gameScene);
		~TrapEvent() = default;

		void onUpdate() override;
		void onEvent() override;

		ICollider& getCollider() override;

	private:
		BoxCollider collider;
		Sprite trapSprite;
	};
}

#endif // !TRAPEVENT_H