#ifndef BULLET_H
#define BULLET_H

#include "Lib.h"
#include "Actor.h"

namespace gnGame {

	class Actor;
	class Enemy;
	class Map;
	class Player;

	using EnemyPtr = std::shared_ptr<Enemy>;

	/// <summary>
	/// 誰が打った弾なのか識別する
	/// </summary>
	enum class BulletType {
		Enemy,   // 敵
		Player,  // プレイヤー
	};

	class Bullet : public Object {
	public:
		Bullet();
		Bullet(const Vector2& _pos, const Vector2& _velocity, BulletType _bulletType = BulletType::Enemy);
		~Bullet() = default;

		void onStart();

		void onUpdate();

		bool isOnScreen();

		void setAttack(float _attack);
		float getAttack();

		bool intersectMap(Map& _map);
		bool hitEnemy(EnemyPtr& _actor);
		bool hitPlayer(Player& _actor);

		BulletType getBulletType();
		ICollider& getCollider();

	private:
		Sprite bulletImage;
		Vector2 velocity;
		BulletType bulletType;
		float attack;
		CircleCollider collider;
		Bounds bounds;
		IntersectPoint intersectPoint;
	};
}

#endif // !BULLET_H
