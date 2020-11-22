#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "Lib.h"
#include "Actor.h"
#include "Map.h"
#include "Parameter.h"

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
	class Player : public IActor{
	public:
		Player();
		~Player() = default;

		void onStart() override;
		void onUpdate() override;

		Vector2 intersectTileMap() override;

		void setMap(Map& _map);

		// 座標をもとに戻す
		void resetPosition();

		void appryDamage(int _damage);

		// コライダーを取得する
		BoxCollider& getCollider();

	private:
		void movePlayer();
		Vector2 verticalIntersect(const Vector2& _nextPos);
		Vector2 holizontalIntersect(const Vector2& _nextPos);
		void shotPlayer();
		void debug();


	private:
		Map map;                     // マップ
		Sprite sprite;               // 画像
		BoxCollider collider;        // コライダー
		PlayerState playerState;     // プレイヤーの移動状態
		ActorParameter parameter;    // プレイヤーのパラメータ
		bool isJump = false;
		bool isGround = false;

		// デバッグ用
		Point pt;
	};

}

#endif // !PLAYER_H
