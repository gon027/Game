#include "TutorialObject.h"
#include "include/Camera.h"
#include "include/TextureManager.h"

namespace gnGame {

	MoveIntro::MoveIntro(const Vector2& _pos)
		: Object()
		, sprite()
	{
		this->transform.setPos(_pos);
		sprite.setTexture(TextureManager::getTexture("Move"));
	}

	void MoveIntro::update()
	{
		auto screen = Camera::toScreenPos(this->transform.pos);
		sprite.draw(screen, Vector2::One, 0.0f, false);
	}

	JumpIntro::JumpIntro(const Vector2& _pos)
		: Object()
		, sprite()
	{
		this->transform.setPos(_pos);
		sprite.setTexture(TextureManager::getTexture("Jump"));
	}

	void JumpIntro::update()
	{
		auto screen = Camera::toScreenPos(this->transform.pos);
		sprite.draw(screen, Vector2::One, 0.0f, false);
	}

	ShotIntro::ShotIntro(const Vector2& _pos)
		: Object()
		, sprite()
	{
		this->transform.setPos(_pos);
		sprite.setTexture(TextureManager::getTexture("Shot"));
	}

	void ShotIntro::update()
	{
		auto screen = Camera::toScreenPos(this->transform.pos);
		sprite.draw(screen, Vector2::One, 0.0f, false);
	}
}