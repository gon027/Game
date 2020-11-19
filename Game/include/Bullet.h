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
	/// �N���ł����e�Ȃ̂����ʂ���
	/// </summary>
	enum class BulletType {
		Enemy,   // �G
		Player,  // �v���C���[
	};

	class Bullet : public Object {
	public:
		Bullet();
		Bullet(const Vector2& _pos, const Vector2& _velocity, BulletType _bulletType = BulletType::Enemy);
		~Bullet() = default;

		void onStart();

		void onUpdate();

		bool intersectMap(Map& _map);
		bool hit(EnemyPtr& _actor);
		bool hit(Player& _actor);

		BulletType getBulletType();
		BoxCollider& getCollider();

	private:
		Vector2 velocity;
		BulletType bulletType;
		BoxCollider boxCollider;
		Rect rect;
		IntersectPoint intersectPoint;
		Bounds bounds;
	};
}

#endif // !BULLET_H
