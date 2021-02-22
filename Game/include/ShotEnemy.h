#ifndef SHOTENEMY_H
#define SHOTENEMY_H

#include "Enemy.h"
#include "EnemyState.h"
#include "FrameTimer.h"

namespace gnGame {

	/// <summary>
	/// 弾を放つ敵
	/// その場から動かず弾を放つ
	/// </summary>
	class ShotEnemy : public Enemy {
	public:
		ShotEnemy();
		ShotEnemy(GameScene* _gameScene, const Vector2& _pos, const ActorParameter _parameter);
		virtual ~ShotEnemy() = default;

		virtual void onStart() override;
		virtual void onUpdate() override;

		void action();

	private:
		GameScene* gameScene;
		FrameTimer frameTime;
		AnimSprite waitAnimSprite;    // 待機用の画像
		AnimSprite actionAnimSprite;  // アニメーション用の画像
		EnemyState::Attack::AimedShotPlayer enemyAttack;
	};

}

#endif // !SHOTENEMY_H