#ifndef ENEMYSTATE_H
#define ENEMYSTATE_H

#include <memory>
#include "Enemy.h"
#include "FrameTimer.h"

namespace gnGame {

	class Player;
	using EnemyPtr = std::shared_ptr<Enemy>;

	namespace EnemyComponent {

		// �v���C���[�̃|�C���^�Ȃ���execute�֐������s����
		struct AttackComponent1 {
			virtual ~AttackComponent1() = default;

			// ���߂����s����
			virtual void execute() = 0;
		};

		// �v���C���[�̃|�C���^���󂯎���Ď��s����
		struct AttackComponent2 {
			virtual ~AttackComponent2() = default;

			// ���߂����s����
			virtual void execute(Player* _player) = 0;
		};
	}

	// �G�̍s���X�e�[�g
	namespace EnemyState {

		// �U���̖��O���
		namespace Attack {

			// �U������
			class EnemyAttack : public EnemyComponent::AttackComponent1 {
			public:
				EnemyAttack(Enemy* _enemyPtr);
				virtual ~EnemyAttack() = default;

				virtual void execute() override;

			protected:
				Enemy* enemyPtr;   // ���g�̃|�C���^
				float shotTime;
			};

			// �v���C���[��_����������
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
