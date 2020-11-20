#include "../include/BackGround.h"
#include "../include/Camera.h"
#include "../include/TextureManager.h"

namespace gnGame {

	BackGround::BackGround(const Vector2& _pos)
		: pos(_pos)
		, backGround()
	{
	}

	void BackGround::setTexture()
	{
		backGround.setTexture(TextureManager::getTexture("Back"));
	}

	void BackGround::draw()
	{
		backGround.draw(Camera::toScreenPos(pos), Vector2::One, 0.0f);
	}
}
