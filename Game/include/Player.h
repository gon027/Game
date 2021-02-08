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
	/// プレイヤーに対してのSEなど
	/// </summary>
	class PlayerAudio {
	public:
		PlayerAudio();
		~PlayerAudio();

		void playAudio(int _index);
		void stopAudio(int _index);

	private:
		std::vector<AudioSource> _audioList;
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

	private:
		void movePlayer();
		Vector2 verticalIntersect(const Vector2& _nextPos);
		Vector2 holizontalIntersect(const Vector2& _nextPos);
		void shotPlayer();
		void debug();

	private:
		Map* map;                    // マップ
		BoxCollider collider;        // コライダー
		PlayerState playerState;     // プレイヤーの移動状態
		PlayerBody playerBody;
		PlayerAudio playerAudio;
		FrameTimer frameTime;
		bool isJump = false;         // ジャンプできるかのフラグ
		bool isGround = false;       // 地面に足がついているかのフラグ
		bool isFall = false;         // 落下しているかのフラグ
		bool jumpInput = false;      // ジャンプボタンが入力されているかのフラグ
		float yPower = 0.0f;
		float time = 0.f;

		AnimSprite waitImage;  // 待機している画像
		AnimSprite walkImage;  // 歩いている画像
	};
}

#endif // !PLAYER_H
