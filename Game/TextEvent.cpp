#include "TextEvent.h"
#include "include/Camera.h"

namespace gnGame {

	TextEvent::TextEvent(const Vector2& _pos)
		: EventObject(_pos)
		, r()
	{
	}

	void TextEvent::onStart()
	{
		
	}

	void TextEvent::onUpdate()
	{
		auto screen = Camera::toScreenPos(this->transform.pos);

		this->collider.update(screen, 32, 32);

		r.setColor(Color{ 255, 128, 0 });
		r.setPos({ screen.x - 16, screen.y - 16 });
		r.setSize(32.f);
		r.draw();
	}

	void TextEvent::onEvent()
	{
		Debug::drawText(300, 300, "dfjeioafjeia");
	}

}
