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

		void onStart() override;

		void onUpdate() override;

		void onEvent() override;

		void setCollisionSize(int _width, int _height);

	private:
		Size size;
		Rect r;
	};

}


#endif // !GOALEVENT_H
