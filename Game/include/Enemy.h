#ifndef ENEMY_H
#define ENEMY_H

#include "Lib.h"
#include "Actor.h"
#include "Map.h"

namespace gnGame {

	/// <summary>
	/// •ûŒü(Œü‚¢‚Ä‚¢‚é•ûŒü, ˆÚ“®‚·‚é•ûŒü)
	/// </summary>
	enum class Direction {
		Up,
		Down,
		Left,
		Right,
	};

	// “GƒNƒ‰ƒX
	class Enemy : public IActor {
	public:
		Enemy();
		Enemy(const Vector2& _pos);
		virtual ~Enemy() = default;

		virtual void onStart() override;
		virtual void onUpdate(float _deltaTime) override;

		virtual Vector2 intersectTileMap() override;

		void setMap(Map& _map);

	private:
		Map map;
		Direction dir;
		Sprite sprite;
		bool isFlip = true;
	};
}

#endif // !ENEMY_H