#ifndef STAGEEVENT_H
#define STAGEEVENT_H

#include "Lib.h"
#include "EventObject.h"

namespace gnGame {

	class StageEvent : public EventObject
	{
	public:
		StageEvent(const Vector2& _pos, Game* _gameScene);
		~StageEvent() = default;

		void onStart() override;

		void onUpdate() override;

		void onEvent() override;

	private:
		Rect r;
	};
}


#endif // !STAGEEVENT_H
