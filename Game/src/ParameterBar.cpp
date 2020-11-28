#include "../include/ParameterBar.h"
#include "../include/TextureManager.h"

namespace gnGame {

	namespace {
		constexpr float ParamBarWidth = 250.0f;
	}

	HpBar::HpBar()
		: IParameterBar()
		, back()
		, barLine()
	{
		back.setTexture(TextureManager::getTexture("HPFrame"));
		barLine.setTexture(TextureManager::getTexture("HPBar"));
	}

	void HpBar::onUpdate(float _x, float _y, float _value, float maxSize)
	{
		float magnification = (_value / maxSize);

		float size = 7.8125f * magnification;
		float a = 16.0f * 6.8125f * magnification + (-16 * (1 - magnification));
		float xPos = _x + a;

		back.draw({ _x, _y }, { 1.0f, 1.0f }, 0.0f, false);
		barLine.draw({ xPos, _y }, { size, 1.0f }, 0.0f, false);
	}

	MpBar::MpBar()
		: IParameterBar()
		, back()
		, barLine()
	{
		back.setTexture(TextureManager::getTexture("MPFrame"));
		barLine.setTexture(TextureManager::getTexture("MPBar"));
	}

	void MpBar::onUpdate(float _x, float _y, float _value, float maxSize)
	{
		float magnification = (_value / maxSize);

		float size = 7.8125f * magnification;
		float a = 16.0f * 6.8125f * magnification - (16 * (1 - magnification));
		float xPos = _x + a;

		back.draw({ _x, _y }, { 1.0f, 1.0f }, 0.0f, false);
		barLine.draw({ xPos, _y }, { size, 1.0f }, 0.0f, false);
	}
}
