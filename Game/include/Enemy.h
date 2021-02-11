#ifndef ENEMY_H
#define ENEMY_H

#include "Actor.h"
#include "Map.h"
#include "../EnemyBody.h"

namespace gnGame {

	enum class EnemyActionState {
		Wait,     // 待機
		Action    // 行動(移動や攻撃などはここ。今後分けるかもしれない)
	};

	// 敵のタイプ
	enum class EnemyType {
		Nomal,     // 普通の敵
		Boss,      // ボス
	};

	// 敵クラス(ベースクラス)
	class Enemy : public IActor {
	public:
		Enemy();
		Enemy(const Vector2& _pos, const ActorParameter _parameter, const EnemyType _enemyType = EnemyType::Nomal);
		virtual ~Enemy() = default;

		virtual void onStart() override;
		virtual void onUpdate() override;

		virtual Vector2 intersectTileMap() override;

		// マップを設定する
		void setMap(Map* _map);

		// 現在の向いている方向を取得する
		Direction getDir();

		// 敵のコライダーを取得
		BoxCollider& getCollider();

		// 敵の体力などの情報のクラスを取得
		EnemyBody& getEnemyBody();

		// 敵のパラメータを取得
		ActorParameter& getParameter();

		// 敵が普通の敵かボスかのタイプを取得する
		const EnemyType getEnemyType();

	protected:
		void moveEnemy();

	protected:
		Map* map;                        // マップのポインタ
		Direction dir;                   // 向いている方角
		Sprite sprite;                   // 画像 (消す可能性あり)
		bool isGround;                   // 地面についているか
		BoxCollider collider;            // コライダー
		EnemyBody enemyBody;             // 敵の体力情報
		EnemyType enemyType;             // 敵のタイプ
		EnemyActionState actionState;    // 敵の行動状態
	};
}

#endif // !ENEMY_H