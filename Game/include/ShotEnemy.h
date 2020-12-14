#ifndef SHOTENEMY_H
#define SHOTENEMY_H

#include "Enemy.h"
#include "EnemyState.h"

namespace gnGame {

	namespace EnemyState {

		class BulletAttack1 : public Attack::EnemyAttack {
		public:
			BulletAttack1(Enemy* _enemyPtr);
			~BulletAttack1() = default;

			virtual void execute() override;
		};
	}

	/// <summary>
	/// ’e‚ð•ú‚Â“G
	/// </summary>
	class ShotEnemy : public Enemy {
	public:
		ShotEnemy();
		ShotEnemy(const Vector2& _pos);
		virtual ~ShotEnemy() = default;

		virtual void onStart() override;
		virtual void onUpdate() override;

	private:
		EnemyState::Attack::EnemyAttack enemyAttack;
		EnemyState::BulletAttack1 aa;
	};

}

#endif // !SHOTENEMY_H