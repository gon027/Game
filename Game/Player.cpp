#include "Player.h"

namespace gnGame {

	constexpr float gravity = 0.98f;

	PlayerImage::PlayerImage()
		: texture("Image/char.png")
		, sprite(texture)
	{
	}

	Player::Player()
		: pImage()
		, pos()
		, velocity()
	{
	}

	void Player::onStart()
	{

	}

	void Player::onUpdate()
	{

		if (Input::getKey(Key::A)) {
			pos.x -= 2.0f;
		}

		if (Input::getKey(Key::D)) {
			pos.x += 2.0f;
		}

		pos.y += gravity;

		pImage.sprite.setPos(pos);
		pImage.sprite.draw();
	}

}