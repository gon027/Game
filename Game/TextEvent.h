#ifndef TEXTEVENT_H
#define TEXTEVENT_H

#include "include/EventObject.h"

namespace gnGame {

	class TextEvent : public EventObject {
	public:
		TextEvent(const Vector2& _pos);
		~TextEvent() = default;

		void onStart() override;
		void onUpdate() override;

		void onEvent() override;

	private:
		Rect r;
	};
}

#endif // !TEXTEVENT_H
