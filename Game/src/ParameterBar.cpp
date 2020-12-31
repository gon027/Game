#include "../include/ParameterBar.h"
#include "../include/TextureManager.h"
#include "../include/UIDrawer.h"

namespace gnGame {

	namespace {
		constexpr float ParamBarWidth = 250.0f;
	}

	HpBar::HpBar()
		: IParameterBar()
		, value(0.0f)
		, barPos()
		, barLinePos()
		, barLineScale(Vector2::One)
		, back()
		, barLine()
		, numberFont(32, "SODA")
	{
		back.setTexture(TextureManager::getTexture("HPFrame"));
		barLine.setTexture(TextureManager::getTexture("HPBar"));

		UIDrawer::getIns()->addUI(this);
	}

	void HpBar::onUpdate(float _x, float _y, float _value, float maxSize)
	{
		value = _value;

		float magnification = (_value / maxSize);
		float barSize = 7.8125f * magnification;
		float xPos = _x + 16.0f * 6.8125f * magnification + (-16.0f * (1.0f - magnification));

		barPos.setPos(_x, _y);
		barLinePos.setPos(xPos, _y);
		barLineScale.setPos(barSize, 1.0f);
	}

	void HpBar::OnDraw()
	{
		back.draw(barPos, { 1.0f, 1.0f }, 0.0f, false);
		barLine.draw(barLinePos, barLineScale, 0.0f, false);

		numberFont.drawText(10, 0, Color::White, "%d", static_cast<int>(value));
	}

	MpBar::MpBar()
		: IParameterBar()
		, value(0.0f)
		, barPos()
		, barLinePos()
		, barLineScale(Vector2::One)
		, back()
		, barLine()
		, numberFont(32, "SODA")
	{
		back.setTexture(TextureManager::getTexture("MPFrame"));
		barLine.setTexture(TextureManager::getTexture("MPBar"));

		UIDrawer::getIns()->addUI(this);
	}

	void MpBar::onUpdate(float _x, float _y, float _value, float maxSize)
	{
		value = _value;

		float magnification = (_value / maxSize);
		float size = 7.8125f * magnification;
		float xPos = _x + 16.0f * 6.8125f * magnification - (16 * (1 - magnification));

		barPos.setPos(_x, _y);
		barLinePos.setPos(xPos, _y);
		barLineScale.setPos(size, 1.0f);
	}

	void MpBar::OnDraw()
	{
		back.draw(barPos, { 1.0f, 1.0f }, 0.0f, false);
		barLine.draw(barLinePos, barLineScale, 0.0f, false);

		numberFont.drawText(10, 32, Color::White, "%d", static_cast<int>(value));
	}
}
