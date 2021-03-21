#ifndef BOSSSTATE_H
#define BOSSSTATE_H

#include "Lib.h"
#include "../FrameTimer.h"

namespace gnGame {

	class Boss;
	class GameScene;

	/// <summary>
	/// �{�X�̍s���p�^�[��
	/// </summary>
	enum class BossPattern {
		Wait = 0,
		TargetPlayerShot,
		ScatterShot,
		LinearShot,
		MoveRight,
		MoveLeft,
		MoveAttackRight,
		MoveAttackLeft,
	};

	namespace BossAction {

		struct BossOrderComponent {
			virtual ~BossOrderComponent() = default;
			virtual void update(Boss* _boss) = 0;
		};

		/// <summary>
		/// �{�X���ҋ@
		/// </summary>
		class BossWait : public BossOrderComponent {
		public:
			BossWait(float waitTime = 1.5f);
			~BossWait() = default;

			void update(Boss* _boss) override;

		private:
			float waitTime;
			float maxWaitTime;
		};

		/// <summary>
		/// ������E�Ɉړ�����
		/// </summary>
		class BossMoveRight : public BossOrderComponent {
		public:
			BossMoveRight(Boss* _boss);
			~BossMoveRight() = default;

			void update(Boss* _boss) override;
		};

		/// <summary>
		/// �E���獶�Ɉړ�
		/// </summary>
		class BossMoveLeft : public BossOrderComponent {
		public:
			BossMoveLeft(Boss* _boss);
			~BossMoveLeft() = default;

			void update(Boss* _boss) override;
		};

		/// <summary>
		/// �E�Ɉړ����Ȃ���e������
		/// </summary>
		class BossMoveShotRight : public BossOrderComponent {
		public:
			BossMoveShotRight(Boss* _boss);
			~BossMoveShotRight() = default;

			void update(Boss * _boss) override;

		private:
			float shotTime;
		};

		/// <summary>
		/// ���Ɉړ����Ȃ���e������
		/// </summary>
		class BossMoveShotLeft : public BossOrderComponent {
		public:
			BossMoveShotLeft(Boss* _boss);
			~BossMoveShotLeft() = default;

			void update(Boss* _boss) override;

		private:
			float shotTime;
		};

		/// <summary>
		/// �v���C���[�Ɍ������đł�
		/// </summary>
		class TargetPlayerShot : public BossOrderComponent {
		public:
			TargetPlayerShot(GameScene* _gameScene);
			~TargetPlayerShot() = default;

			void update(Boss* _boss) override;

		private:
			GameScene* gameScene;
			float actionTime;
			float shotTime;
		};

		/// <summary>
		/// �v���C���[�̈ʒu������̊p�x����e������
		/// </summary>
		class ScatterShot : public BossOrderComponent {
		private:
			static constexpr float Range = 30.0f;

		public:
			ScatterShot(GameScene* _gameScene);
			~ScatterShot() = default;

			void update(Boss* _boss) override;

		private:
			GameScene* gameScene;
			float actionTime;
			float shotTime;
		};

		/// <summary>
		/// �����ɒe������
		/// </summary>
		class LinearShot : public BossOrderComponent {
		public:
			LinearShot();
			~LinearShot() = default;

			void update(Boss * _boss) override;

		private:
			float actionTime;
			float shotTime;
		};
	}
}

#endif // !BOSSSTATE_H