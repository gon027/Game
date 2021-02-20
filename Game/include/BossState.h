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
		Wait    = 0,
		Attack1,
		Attack2,
		Attack3,
		Move1,
		Move2,
	};

	namespace BossAction {

		struct BossOrderComponent {
			virtual ~BossOrderComponent() = default;
			virtual void update(Boss* _boss) = 0;
		};

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
		class BossMove1 : public BossOrderComponent {
		public:
			BossMove1();
			~BossMove1() = default;

			void update(Boss* _boss) override;
		};

		/// <summary>
		/// �E���獶�Ɉړ�
		/// </summary>
		class BossMove2 : public BossOrderComponent {
		public:
			BossMove2();
			~BossMove2() = default;

			void update(Boss* _boss) override;
		};

		/// <summary>
		/// �v���C���[�Ɍ������đł�
		/// </summary>
		class BossAction1 : public BossOrderComponent {
		public:
			BossAction1(GameScene* _gameScene);
			~BossAction1() = default;

			void update(Boss* _boss) override;

		private:
			GameScene* gameScene;
			float actionTime;
			float shotTime;
		};

		/// <summary>
		/// �v���C���[�̈ʒu������̊p�x����e������
		/// </summary>
		class BossAction2 : public BossOrderComponent {
		private:
			static constexpr float Range = 30.0f;

		public:
			BossAction2(GameScene* _gameScene);
			~BossAction2() = default;

			void update(Boss* _boss) override;

		private:
			GameScene* gameScene;
			float actionTime;
			float shotTime;
		};

		/// <summary>
		/// �S���ʂɒe������
		/// </summary>
		class BossAction3 : public BossOrderComponent {
		public:
			BossAction3();
			~BossAction3() = default;

			void update(Boss* _boss) override;

		private:
			float actionTime;
			float shotTime;
		};
	}
}

#endif // !BOSSSTATE_H