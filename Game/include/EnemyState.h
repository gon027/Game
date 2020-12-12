#ifndef ENEMYSTATE_H
#define ENEMYSTATE_H

#include <memory>
#include "Enemy.h"

namespace gnGame {

	class Player;
	using EnemyPtr = std::shared_ptr<Enemy>;

	namespace EnemyComponent {

		// ���߂̊��N���X
		struct OrderComponent {
			virtual ~OrderComponent() = default;

			// ���߂����s����
			virtual void execute() = 0;
		};
	}

	// �G�̍s���X�e�[�g
	namespace EnemyState {

		// �ړ��̖��O���
		namespace Move {

			// �ړ�������
			class EnemyMove : public EnemyComponent::OrderComponent {
			public:
				EnemyMove(Enemy* _enemyPtr, Player* _player);
				virtual ~EnemyMove() = default;

				virtual void execute() override;

			private:
				Enemy* enemyPtr;    // ���g�̃|�C���^
				Player* playerPtr;
			};

		}

		// �U���̖��O���
		namespace Attack {

			// �U������
			class EnemyAttack : public EnemyComponent::OrderComponent {
			public:
				EnemyAttack(Enemy* _enemyPtr);
				virtual ~EnemyAttack() = default;

				virtual void execute() override;

			private:
				Enemy* enemyPtr;   // ���g�̃|�C���^
				float shotTime;
			};

		}
	}
}

#endif // !ENEMYSTATE_H
