#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "Lib.h"
#include "Actor.h"
#include "Map.h"
#include "Parameter.h"
#include "PlayerBody.h"
#include "../FrameTimer.h"

namespace gnGame {

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
	class Player : public Actor{
	public:
		Player();
		~Player() = default;

		void onStart() override;
		void onUpdate() override;

		Vector2 intersectTileMap() override;

		void setMap(Map* _map);

		// 座標をもとに戻す
		void resetPosition(const Vector2& _pos);

		// コライダーを取得する
		BoxCollider& getCollider();

		PlayerBody& getPlayerBody();

		// 死亡したときの処理
		void death();

		// リスポーン
		void respawn(const Vector2& _pos);

		// 速度などをリセット
		void reset();

		// 一時的に操作不可能にする
		void setIsMove(bool _isMove);

	private:
		void movePlayer();
		void jumpPlayer();
		Vector2 verticalIntersect(const Vector2& _nextPos);
		Vector2 holizontalIntersect(const Vector2& _nextPos);
		void shotPlayer();
		void debug();

	private:
		Map* map;                    // マップのポインタ
		BoxCollider collider;        // コライダー
		PlayerState playerState;     // プレイヤーの移動状態
		PlayerBody playerBody;
		FrameTimer moveTime;
		FrameTimer jumpTime;
		bool isJump;                 // ジャンプできるかのフラグ
		bool isGround;               // 地面に足がついているかのフラグ
		bool isFall;                 // 落下しているかのフラグ
		bool jumpInput;              // ジャンプボタンが入力されているかのフラグ
		bool isMove;

		AnimSprite waitImage;  // 待機している画像
		AnimSprite walkImage;  // 歩いている画像
	};
}

#endif // !PLAYER_H
