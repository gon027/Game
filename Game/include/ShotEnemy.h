#ifndef SHOTENEMY_H
#define SHOTENEMY_H

#include "Enemy.h"
#include "EnemyState.h"

namespace gnGame {

	namespace EnemyState {

		class BulletShotPattern1 : public Attack::EnemyAttack {
		public:
			BulletShotPattern1(Enemy* _enemyPtr);
			~BulletShotPattern1() = default;

			virtual void execute() override;
		};
	}

	/// <summary>
	/// 弾を放つ敵
	/// その場から動かず弾を放つ
	/// </summary>
	class ShotEnemy : public Enemy {
	public:
		ShotEnemy();
		ShotEnemy(const Vector2& _pos, const ActorParameter _parameter);
		virtual ~ShotEnemy() = default;

		virtual void onStart() override;
		virtual void onUpdate() override;

	private:
		//AnimSprite waitAnimSprite;    //待機用の画像
		AnimSprite actionAnimSprite;  // アニメーション用の画像
		EnemyState::Attack::EnemyAttack enemyAttack;
		EnemyState::BulletShotPattern1 bShotPattern1;
	};

}

#endif // !SHOTENEMY_H