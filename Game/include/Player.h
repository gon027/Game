#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "Lib.h"
#include "Actor.h"
#include "Map.h"

using std::vector;

namespace gnGame {

	class Camera;

	// プレイヤーの画像
	struct PlayerImage {
		Texture texture;
		Sprite sprite;

		PlayerImage();
		~PlayerImage() = default;
	};

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

		float aaaa = 0.0f;

		// デバッグ用
		PlayerImage pImage;
		Point pt;
	};

}

#endif // !PLAYER_H
