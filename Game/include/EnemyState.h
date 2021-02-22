#ifndef ENEMYSTATE_H
#define ENEMYSTATE_H

#include <memory>
#include "Enemy.h"
#include "FrameTimer.h"

namespace gnGame {

	class Player;
	using EnemyPtr = std::shared_ptr<Enemy>;

	namespace EnemyComponent {

		// プレイヤーのポインタなしにexecute関数を実行する
		struct AttackComponent1 {
			virtual ~AttackComponent1() = default;

			// 命令を実行する
			virtual void execute() = 0;
		};

		// プレイヤーのポインタを受け取って実行する
		struct AttackComponent2 {
			virtual ~AttackComponent2() = default;

			// 命令を実行する
			virtual void execute(Player* _player) = 0;
		};
	}

	// 敵の行動ステート
	namespace EnemyState {

		// 攻撃の名前空間
		namespace Attack {

			// 攻撃する
			class EnemyAttack : public EnemyComponent::AttackComponent1 {
			public:
				EnemyAttack(Enemy* _enemyPtr);
				virtual ~EnemyAttack() = default;

				virtual void execute() override;

			protected:
				Enemy* enemyPtr;   // 自身のポインタ
				float shotTime;
			};

			// プレイヤーを狙い撃ちする
			class AimedShotPlayer : public EnemyComponent::AttackComponent2 {
			public:
				AimedShotPlayer(Enemy* _enemyPtr);
				virtual ~AimedShotPlayer() = default;

				virtual void execute(Player* _player);

			protected:
				Enemy* enemyPtr;
				FrameTimer frameTime;
			};

		}
	}
}

#endif // !ENEMYSTATE_H
