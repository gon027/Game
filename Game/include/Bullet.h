#ifndef BULLET_H
#define BULLET_H

#include "Lib.h"
#include "Actor.h"

namespace gnGame {

	class IActor;
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
		bool hit(EnemyPtr& _actor);
		bool hit(Player& _actor);

		BulletType getBulletType();
		BoxCollider& getCollider();

	private:
		Vector2 velocity;
		BulletType bulletType;
		BoxCollider collider;
		Sprite bulletImage;
		IntersectPoint intersectPoint;
		Bounds bounds;
		float attack;
	};
}

#endif // !BULLET_H
