#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "Lib.h"
#include "Actor.h"
#include "Map.h"
#include "ActorMove.h"
#include "Parameter.h"
#include "PlayerBody.h"

namespace gnGame {

	class Player;

	using std::vector;

	// プレイヤーの状態
	enum class PlayerState {
		Wait,            // 待機中
		Move,         // 移動中
		FirstJump,       // 1回目のジャンプ
		Fall,            // 落下中
	};

	/// <summary>
	/// プレイヤークラス
	/// </summary>
	class Player : public IActor{
	public:
		Player();
		//Player(Map* _map);
		~Player() = default;

		void onStart() override;
		void onUpdate() override;

		Vector2 intersectTileMap() override;

		void setMap(Map* _map);

		// 座標をもとに戻す
		void resetPosition();

		// コライダーを取得する
		BoxCollider& getCollider();

		PlayerBody& getPlayerBody();

	private:
		void movePlayer();
		Vector2 verticalIntersect(const Vector2& _nextPos);
		Vector2 holizontalIntersect(const Vector2& _nextPos);
		void shotPlayer();
		void debug();

	private:
		Map* map;                     // マップ
		Sprite sprite;               // 画像
		BoxCollider collider;        // コライダー
		PlayerState playerState;     // プレイヤーの移動状態
		PlayerBody playerBody;
		bool isJump = false;
		bool isGround = false;
		bool isDamage = false;
		float invincibleTime = 0.0f;    // 無敵時間

		// デバッグ用
		Point pt;
	};

	// プレイヤーを移動させるクラス
	class PlayerMove : public ActorMove {
	public:
		PlayerMove(Player* _player);
		~PlayerMove() = default;

		void moveActor() override;

		Player* player;
	};

}

#endif // !PLAYER_H
