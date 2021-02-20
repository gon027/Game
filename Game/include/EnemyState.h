#ifndef ENEMYSTATE_H
#define ENEMYSTATE_H

#include <memory>
#include "Enemy.h"
#include "FrameTimer.h"

namespace gnGame {

	class Player;
	using EnemyPtr = std::shared_ptr<Enemy>;

	namespace EnemyComponent {

		// 命令の基底クラス

		struct IActAble {
			virtual ~IActAble() = default;

			virtual void action(class IActor* _actor) = 0;
		};

		// プレイヤーのポインタなしにexecute関数を実行する
		struct OrderComponent {
			virtual ~OrderComponent() = default;

			// 命令を実行する
			virtual void execute() = 0;
		};

		// プレイヤーのポインタを受け取って実行する
		struct AttackComponent {
			virtual ~AttackComponent() = default;

			// 命令を実行する
			virtual void execute(Player* _player) = 0;
		};
	}

	// 敵の行動ステート
	namespace EnemyState {

		// 移動の名前空間
		namespace Move {

			// 移動させる
			class EnemyMove : public EnemyComponent::OrderComponent {
			public:
				EnemyMove(Enemy* _enemyPtr);
				virtual ~EnemyMove() = default;

				virtual void execute() override;

			private:
				Enemy* enemyPtr;    // 自身のポインタ
				Vector2 velocity;
			};

		}

		// 攻撃の名前空間
		namespace Attack {

			// 攻撃する
			class EnemyAttack : public EnemyComponent::OrderComponent {
			public:
				EnemyAttack(Enemy* _enemyPtr);
				virtual ~EnemyAttack() = default;

				virtual void execute() override;

			protected:
				Enemy* enemyPtr;   // 自身のポインタ
				float shotTime;
			};

			// プレイヤーを狙い撃ちする
			class AimedShotPlayer : public EnemyComponent::AttackComponent {
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
