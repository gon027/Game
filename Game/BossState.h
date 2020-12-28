#ifndef BOSSSTATE_H
#define BOSSSTATE_H

#include "include/Lib.h"

namespace gnGame {

	class Boss;

	/// <summary>
	/// ボスの行動パターン
	/// </summary>
	enum class BossPattern {
		Wait    = 0,
		Move1   = 1,
		Move2   = 2,
		Attack1 = 10,
		Attack2 = 11,
		Attack3 = 12,
	};

	namespace BossAction {

		struct BossOrderComponent {
			virtual ~BossOrderComponent() = default;
			virtual void update(Boss* _boss) = 0;
		};

		class BossWait : public BossOrderComponent {
		private:
			// 最大の待ち時間
			static constexpr float MaxWaitTime = 3.0f;

		public:
			BossWait();
			~BossWait() = default;

			void update(Boss* _boss) override;

		private:
			float waitTime;
		};

		/// <summary>
		/// 左から右に移動する
		/// </summary>
		class BossMove1 : public BossOrderComponent {
		private:
			static Vector2 TargetPoint;

		public:
			BossMove1();
			~BossMove1() = default;

			void update(Boss* _boss) override;

		private:
			float moveTime;
		};

		/// <summary>
		/// 右から左に移動
		/// </summary>
		class BossMove2 : public BossOrderComponent {
		private:
			static Vector2 TargetPoint;

		public:
			BossMove2();
			~BossMove2() = default;

			void update(Boss* _boss) override;

		private:
			float moveTime;
		};

		/// <summary>
		/// プレイヤーに向かって打つ
		/// </summary>
		class BossAction1 : public BossOrderComponent {
		public:
			BossAction1();
			~BossAction1() = default;

			void update(Boss* _boss) override;

		private:
			float actionTime;
			float shotTime;
		};

		/// <summary>
		/// プレイヤーの位置から一定の角度から弾を撃つ
		/// </summary>
		class BossAction2 : public BossOrderComponent {
		private:
			static constexpr float Range = 30.0f;

		public:
			BossAction2();
			~BossAction2() = default;

			void update(Boss* _boss) override;

		private:
			float actionTime;
			float shotTime;
		};

		/// <summary>
		/// 全方位に弾を撃つ
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