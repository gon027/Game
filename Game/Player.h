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

	// プレイヤーの当たり判定
	struct PlayerHit {
		static const int Size = 2;

		vector<Vector2> right;
		vector<Vector2> left;
		vector<Vector2> top;
		vector<Vector2> bottom;

		PlayerHit()
			: right(Size)
			, left(Size)
			, top(Size)
			, bottom(Size)
		{}
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

		//void move();
		//void jump();

		void debug();

		const Vector2& getPos();
		const Vector2& getVelocity();

	private:
		Camera* camera;
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
