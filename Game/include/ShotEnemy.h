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
		ShotEnemy(GameScene* _gameScene, const Vector2& _pos, const ActorParameter _parameter, Direction _direction);
		virtual ~ShotEnemy() = default;

		virtual void onStart() override;
		virtual void onUpdate() override;

		void action();

	private:
		GameScene* gameScene;
		AnimSprite waitAnimSprite;    // 待機用の画像
		EnemyState::Attack::EnemyAttack enemyAttack;
	};

}

#endif // !SHOTENEMY_H