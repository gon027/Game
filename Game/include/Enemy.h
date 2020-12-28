#ifndef ENEMY_H
#define ENEMY_H

#include "Actor.h"
#include "Map.h"
#include "../EnemyBody.h"

namespace gnGame {

	// 敵クラス(ベースクラス)
	class Enemy : public IActor {
	public:
		Enemy();
		Enemy(const Vector2& _pos, const ActorParameter _parameter);
		virtual ~Enemy() = default;

		virtual void onStart() override;
		virtual void onUpdate() override;

		virtual Vector2 intersectTileMap() override;

		void setMap(Map* _map);

		Direction getDir();

		BoxCollider& getCollider();

		EnemyBody& getEnemyBody();
		ActorParameter& getParameter();

	protected:
		void moveEnemy();

	protected:
		Map* map;
		Direction dir;
		Sprite sprite;
		int bframe = 0;
		BoxCollider collider;
		EnemyBody enemyBody;
	};
}

#endif // !ENEMY_H