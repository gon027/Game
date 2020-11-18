#ifndef ENEMY_H
#define ENEMY_H

#include "Lib.h"
#include "Actor.h"
#include "Map.h"

namespace gnGame {

	/// <summary>
	/// ����(�����Ă������, �ړ��������)
	/// </summary>
	enum class Direction {
		Up,
		Down,
		Left,
		Right,
	};

	// �G�N���X
	class Enemy : public IActor {
	public:
		Enemy();
		Enemy(const Vector2& _pos);
		virtual ~Enemy() = default;

		virtual void onStart() override;
		virtual void onUpdate() override;

		virtual Vector2 intersectTileMap() override;

		void setMap(Map& _map);

		BoxCollider& getCollider();

	private:
		void moveEnemy();
		void shotEnemy();

	private:
		Map map;
		Direction dir;
		Sprite sprite;
		bool isFlip = true;
		int bframe = 0;
		BoxCollider boxCollider;
	};
}

#endif // !ENEMY_H