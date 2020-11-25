#ifndef ENEMY_H
#define ENEMY_H

#include "Actor.h"
#include "Map.h"

namespace gnGame {

	/// <summary>
	/// 方向(向いている方向, 移動する方向)
	/// </summary>
	enum class Direction {
		Up,
		Down,
		Left,
		Right,
	};

	// 敵クラス(ベースクラス)
	class Enemy : public IActor {
	public:
		Enemy();
		Enemy(const Vector2& _pos);
		virtual ~Enemy() = default;

		virtual void onStart() override;
		virtual void onUpdate() override;

		virtual Vector2 intersectTileMap() override;

		void setMap(Map* _map);

		BoxCollider& getCollider();

	protected:
		void moveEnemy();
		void shotEnemy();

	protected:
		Map* map;
		Direction dir;
		Sprite sprite;
		int bframe = 0;
		BoxCollider collider;
	};
}

#endif // !ENEMY_H