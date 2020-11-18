#include "Bullet.h"

namespace gnGame {

	Bullet::Bullet(const Vector2& _pos, const Vector2& _velocity)
		: velocity(_velocity)
		, rect()
	{
		this->transform.setPos(_pos);
	}

	void Bullet::onStart()
	{
		rect.setSize(15.f);
		rect.setColor(Color::Blue);
	}

	void Bullet::onUpdate()
	{
		this->transform.pos += velocity;
		rect.setPos(this->transform.pos);
		rect.draw();
	}

}
