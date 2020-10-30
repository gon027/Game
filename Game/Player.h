#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "Lib.h"
#include "Actor.h"
#include "Map.h"

using std::vector;

namespace gnGame {

	// プレイヤーの画像
	struct PlayerImage {
		Texture texture;
		Sprite sprite;

		PlayerImage();
		~PlayerImage() = default;
	};

	// プレイヤーの移動に関する情報
	struct PlayerMoveInfo {
		PlayerMoveInfo();
		~PlayerMoveInfo() = default;

		bool isJump;         // ジャンプできるか
		bool isSecondJump;   // 2回目のジャンプできるか
		bool isGround;       // 地面に着地しているか
	};

	// プレイヤーの当たり判定
	struct PlayerHit {
		vector<Vector2> right;
		vector<Vector2> left;
		vector<Vector2> top;
		vector<Vector2> bottom;

		PlayerHit()
			: right(2)
			, left(2)
			, top(2)
			, bottom(2)
		{}
	};
	
	// プレイヤー本体
	class Player : public IActor{
	public:
		Player(Map& _map);
		~Player() = default;

		void onStart() override;
		void onUpdate() override;

		//void move();
		//void jump();

		void debug();

	private:
		Map map;

		PlayerImage pImage;
		Vector2 pos;          // 座標
		Vector2 velocity;     // 速度
		Bounds bounds;
		PlayerHit pHit;
		// PlayerMoveInfo pmInfo;

		bool isJump = false;
		bool isGround = false;

		// デバッグ用
		Point pt;
	};

}

#endif // !PLAYER_H
