#include "../include/ParameterBar.h"

namespace gnGame {

	namespace {
		constexpr float ParamBarWidth = 250.0f;
	}

	ParameterBar::ParameterBar()
		: Object()
		, rect()
	{
	}

	void ParameterBar::onUpdate(float _value, float maxSize)
	{
		this->transform.pos.setPos(0.0f, 0.0f);

		float size = ParamBarWidth * (_value / maxSize);
		
		rect.setColor(Color::Green);
		rect.setSize(size, 35.f);
		rect.setPos(this->transform.pos);
		rect.draw();
	}
}
