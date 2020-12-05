#ifndef GOALEVENT_H
#define GOALEVENT_H

#include "EventObject.h"

namespace gnGame {

	class GoalEvent : public EventObject
	{
	public:
		GoalEvent(const Vector2& _pos, Game* _gameScene);
		~GoalEvent() = default;

		void onStart() override;

		void onUpdate() override;

		void onEvent() override;

	private:
		Rect r;
	};

}


#endif // !GOALEVENT_H
