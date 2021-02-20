#ifndef ENEMYSTATE_H
#define ENEMYSTATE_H

#include <memory>
#include "Enemy.h"
#include "FrameTimer.h"

namespace gnGame {

	class Player;
	using EnemyPtr = std::shared_ptr<Enemy>;

	namespace EnemyComponent {

		// ���߂̊��N���X

		struct IActAble {
			virtual ~IActAble() = default;

			virtual void action(class IActor* _actor) = 0;
		};

		// �v���C���[�̃|�C���^�Ȃ���execute�֐������s����
		struct OrderComponent {
			virtual ~OrderComponent() = default;

			// ���߂����s����
			virtual void execute() = 0;
		};

		// �v���C���[�̃|�C���^���󂯎���Ď��s����
		struct AttackComponent {
			virtual ~AttackComponent() = default;

			// ���߂����s����
			virtual void execute(Player* _player) = 0;
		};
	}

	// �G�̍s���X�e�[�g
	namespace EnemyState {

		// �ړ��̖��O���
		namespace Move {

			// �ړ�������
			class EnemyMove : public EnemyComponent::OrderComponent {
			public:
				EnemyMove(Enemy* _enemyPtr);
				virtual ~EnemyMove() = default;

				virtual void execute() override;

			private:
				Enemy* enemyPtr;    // ���g�̃|�C���^
				Vector2 velocity;
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

			protected:
				Enemy* enemyPtr;   // ���g�̃|�C���^
				float shotTime;
			};

			// �v���C���[��_����������
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
