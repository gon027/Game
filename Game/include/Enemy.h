#ifndef ENEMY_H
#define ENEMY_H

#include "Lib.h"
#include "Actor.h"
#include "Map.h"

namespace gnGame {

	struct EnemyImage {
		EnemyImage() 
			: texture("Asset/Image/Enemy.png")
			, sprite(texture)
		{}

		Texture texture;
		Sprite sprite;
	};

	/// <summary>
	/// •ûŒü(Œü‚¢‚Ä‚¢‚é•ûŒü, ˆÚ“®‚·‚é•ûŒü)
	/// </summary>
	enum class Direction {
		Up,
		Down,
		Left,
		Right,
	};

	class Enemy : public IActor {
	public:
		Enemy();
		virtual ~Enemy() = default;

		virtual void onStart() override;
		virtual void onUpdate(float _deltaTime) override;

		virtual Vector2 intersectTileMap() override;

		void setMap(Map& _map);

	private:
		Map map;
		Direction dir;

		EnemyImage eImage;
		bool isFlip = true;
	};
}

#endif // !ENEMY_H