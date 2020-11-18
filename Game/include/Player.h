#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "Lib.h"
#include "Actor.h"
#include "Map.h"
#include "Bullet.h"

using std::vector;

namespace gnGame {

	class Camera;

	// プレイヤーの移動に関する情報
	struct PlayerMoveInfo {
		bool isJump;         // ジャンプできるか
		bool isSecondJump;   // 2回目のジャンプできるか
		bool isGround;       // 地面に着地しているか

		PlayerMoveInfo();
		~PlayerMoveInfo() = default;
	};

	/// <summary>
	/// プレイヤークラス
	/// </summary>
	class Player : public IActor{
	public:
		Player();
		~Player() = default;

		void onStart() override;
		void onUpdate(float _deltaTime) override;

		Vector2 intersectTileMap() override;

		void setMap(Map& _map);

		// 座標をもとに戻す
		void resetPosition();

		void debug();

	private:
		Map map;
		
		bool isJump = false;
		bool isGround = false;
		Sprite sprite;

		// デバッグ用
		Point pt;
		vector<Bullet> bulletList;
	};

}

#endif // !PLAYER_H
