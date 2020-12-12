#ifndef ENEMYSTATE_H
#define ENEMYSTATE_H

#include <memory>
#include "Enemy.h"

namespace gnGame {

	class Player;
	using EnemyPtr = std::shared_ptr<Enemy>;

	namespace EnemyComponent {

		// 命令の基底クラス
		struct OrderComponent {
			virtual ~OrderComponent() = default;

			// 命令を実行する
			virtual void execute() = 0;
		};
	}

	// 敵の行動ステート
	namespace EnemyState {

		// 移動の名前空間
		namespace Move {

			// 移動させる
			class EnemyMove : public EnemyComponent::OrderComponent {
			public:
				EnemyMove(Enemy* _enemyPtr, Player* _player);
				virtual ~EnemyMove() = default;

				virtual void execute() override;

			private:
				Enemy* enemyPtr;    // 自身のポインタ
				Player* playerPtr;
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

			private:
				Enemy* enemyPtr;   // 自身のポインタ
				float shotTime;
			};

		}
	}
}

#endif // !ENEMYSTATE_H
