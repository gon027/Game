#include "TestBullet.h"
#include "Camera.h"
#include "TextureManager.h"
#include "ObjectManager.h"

namespace gnGame {

	TestBullet::TestBullet(const Vector2& _pos, const Vector2& _velocity)
		: sprite()
		, velocity(_velocity)
	{
		this->setName("Bullet");
		this->transform.setPos(_pos);
		sprite.setTexture(TextureManager::getTexture("Yellow_Bullet"));
	}

	void TestBullet::onStart()
	{
	}

	void TestBullet::onUpdate()
	{
		this->transform.pos += velocity;
		auto screen = Camera::toScreenPos(this->transform.pos);
		sprite.draw(screen, Vector2::One, 0.0f);
	}

}