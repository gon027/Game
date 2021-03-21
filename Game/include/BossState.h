#ifndef BOSSSTATE_H
#define BOSSSTATE_H

#include "Lib.h"
#include "../FrameTimer.h"

namespace gnGame {

	class Boss;
	class GameScene;

	/// <summary>
	/// ボスの行動パターン
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
		/// ボスが待機
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
		/// 左から右に移動する
		/// </summary>
		class BossMoveRight : public BossOrderComponent {
		public:
			BossMoveRight(Boss* _boss);
			~BossMoveRight() = default;

			void update(Boss* _boss) override;
		};

		/// <summary>
		/// 右から左に移動
		/// </summary>
		class BossMoveLeft : public BossOrderComponent {
		public:
			BossMoveLeft(Boss* _boss);
			~BossMoveLeft() = default;

			void update(Boss* _boss) override;
		};

		/// <summary>
		/// 右に移動しながら弾を撃つ
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
		/// 左に移動しながら弾を撃つ
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
		/// プレイヤーに向かって打つ
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
		/// プレイヤーの位置から一定の角度から弾を撃つ
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
		/// 直線に弾を撃つ
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