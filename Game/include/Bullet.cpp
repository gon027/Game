#include "Bullet.h"
#include "Camera.h"
#include "Map.h"
#include "Actor.h"
#include "Player.h"
#include "Enemy.h"

namespace gnGame {

	Bullet::Bullet()
		: Bullet(Vector2::Zero, Vector2::Zero, BulletType::Enemy)
	{
	}

	Bullet::Bullet(const Vector2& _pos, const Vector2& _velocity, BulletType _bulletType)
		: velocity(_velocity)
		, bulletType(_bulletType)
		, rect()
	{
		this->transform.setPos(_pos);
	}

	void Bullet::onStart()
	{
		rect.setSize(20.f);
		rect.setColor(Color::Blue);
	}

	void Bullet::onUpdate()
	{
		this->transform.pos += velocity;
		boxCollider.update(this->transform.pos, 20.0f, 20.0f);
		rect.setPos(this->transform.pos);
		rect.draw();
	}

	bool Bullet::hit(EnemyPtr& _actor)
	{
		// Actor‚Æ‚ ‚½‚Á‚½‚Æ‚«‚Ìˆ—

		if (boxCollider.isHitTest(_actor->getCollider())) {
			return true;
		}

		return false;
	}

	BulletType Bullet::getBulletType()
	{
		return bulletType;
	}

	BoxCollider& Bullet::getCollider()
	{
		return boxCollider;
	}

}
