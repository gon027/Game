#include "../include/Bullet.h"
#include "../include/Camera.h"
#include "../include/EnemyManager.h"
#include "../include/TextureManager.h"
#include "../include/Map.h"
#include "../include/Player.h"
#include "../include/Enemy.h"
#include "../include/ObjectManager.h"

namespace gnGame {

	Bullet::Bullet(const Vector2& _pos, const Vector2& _velocity, BulletType _bulletType)
		: GameObject()
		, velocity(_velocity)
		, bulletType(_bulletType)
		, bulletImage()
		, intersectPoint()
		, bounds()
		, attack(1.0f)
	{
		this->setName("Bullet");
		this->transform.setPos(_pos);
		bulletImage.setTexture(TextureManager::getTexture("Yellow_Bullet"));
	}

	void Bullet::onStart()
	{
		bounds.minPos.setPos(0, 0);
		bounds.maxPos.setPos(16, 16);
		bounds.size.setPos(bounds.maxPos - bounds.minPos);
		bounds.center.setPos(bounds.size.half());
	}

	void Bullet::onUpdate()
	{
		this->transform.pos += velocity;
		auto screen = Camera::toScreenPos(this->transform.pos);
		collider.update(screen, 16.0f);
	}

	void Bullet::onDraw()
	{
		auto screen = Camera::toScreenPos(this->transform.pos);
		bulletImage.draw(screen, Vector2::One, 0.0f);
	}

	void Bullet::setAttack(float _attack)
	{
		attack = _attack;
	}

	void Bullet::onCollision(const ActorPtr& _actor)
	{
		_actor->getActorBody().damage(this->attack);

		if (_actor->getActorBody().getParameter().hp <= 0) {
			_actor->setActive(false);
		}

		/*
		// プレイヤーとの当たり判定
		if (_actor->getName() == "Player") {
			//_actor->getActorBody().damage(this->attack);
		}

		// 敵との当たり判定
		if (_actor->getName() == "Enemy") {
			//_actor->getActorBody().damage(this->attack);
		}
		*/
	}

	float Bullet::getAttack()
	{
		return attack;
	}

	/*
	bool Bullet::intersectMap(Map& _map)
	{
		auto nextPos = this->transform.pos;

		// 判定を行う座標を決める
		float offX{ bounds.center.x / 4.0f - 1.0f };
		float offY{ bounds.center.y / 4.0f - 1.0f };

		// 上下判定用のに判定ボックス更新
		bounds.minPos.setPos(this->transform.pos.x - bounds.center.x, nextPos.y - bounds.center.y);
		bounds.maxPos.setPos(this->transform.pos.x + bounds.center.x, nextPos.y + bounds.center.y);

		// -- 下 --
		intersectPoint.bottom[0] = Vector2{ bounds.minPos.x + offX, bounds.maxPos.y + 1.0f };
		intersectPoint.bottom[1] = Vector2{ bounds.maxPos.x - offX, bounds.maxPos.y + 1.0f };

		// -- 上 --
		intersectPoint.top[0] = Vector2{ bounds.minPos.x + offX, bounds.minPos.y - 1.0f };
		intersectPoint.top[1] = Vector2{ bounds.maxPos.x - offX, bounds.minPos.y - 1.0f };

		// -- 上との当たり判定 --
		for (int i{}; i < IntersectPoint::Size; ++i) {
			if (_map.checkTile((int)intersectPoint.top[i].x, (int)intersectPoint.top[i].y)) {
				return true;
			}
		}

		// -- 下との当たり判定 --
		for (int i{}; i < IntersectPoint::Size; ++i) {
			if (_map.checkTile((int)intersectPoint.bottom[i].x, (int)intersectPoint.bottom[i].y)) {
				return true;
			}
		}

		// 左右判定用に判定ボックス更新
		bounds.minPos.setPos(nextPos.x - bounds.center.x, this->transform.pos.y - bounds.center.y);
		bounds.maxPos.setPos(nextPos.x + bounds.center.x, this->transform.pos.y + bounds.center.y);

		// -- 右 --
		intersectPoint.right[0] = Vector2{ bounds.maxPos.x , bounds.minPos.y + offY };
		intersectPoint.right[1] = Vector2{ bounds.maxPos.x , bounds.maxPos.y - offY };

		// -- 左 --
		intersectPoint.left[0] = Vector2{ bounds.minPos.x - 1.0f, bounds.minPos.y + offY };
		intersectPoint.left[1] = Vector2{ bounds.minPos.x - 1.0f, bounds.maxPos.y - offY };


		// -- 右との当たり判定 --
		for (int i{}; i < IntersectPoint::Size; ++i) {
			if (_map.checkTile((int)intersectPoint.right[i].x, (int)intersectPoint.right[i].y)) {
				return true;
			}
		}

		// -- 左との当たり判定 --		
		for (int i{}; i < IntersectPoint::Size; ++i) {
			if (_map.checkTile((int)intersectPoint.left[i].x, (int)intersectPoint.left[i].y)) {
				return true;
			}
		}

		return false;
	}

	// Actor(Enemy)とあたったときの処理
	bool Bullet::hitEnemy(EnemyPtr& _actor)
	{
		return collider.isHitTest(_actor->getCollider());
	}

	// プレイヤーとあたったときの処理
	bool Bullet::hitPlayer(Player& _actor)
	{
		return collider.isHitTest(_actor.getCollider());
	}
	

	BulletType Bullet::getBulletType()
	{
		return bulletType;
	}
	*/

	CircleCollider& Bullet::getCollider()
	{
		return collider;
	}
}
