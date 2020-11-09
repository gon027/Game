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
		Player(Camera* camera, Map& _map);
		~Player() = default;

		void onStart() override;
		void onUpdate() override;

		void setMap(Map& _map);

		// 当たり判定
		Vector2 intersectTileMap() override;

		// 座標をもとに戻す
		void resetPosition();

		void debug();

	private:
		Camera* camera;
		Map map;
		
		bool isJump = false;
		bool isGround = false;

		// デバッグ用
		PlayerImage pImage;
		Point pt;
	};

}

#endif // !PLAYER_H
